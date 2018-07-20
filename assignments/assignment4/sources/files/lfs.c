#include "lfs.h"
#include "fstruct.h"

#define min(x,y) x < y ? x : y
#define max(x,y) x > y ? x : y


FILE * file_system;

typedef struct{
	char* string;
	char* end;
} split_path_t;

split_path_t split_path(const char * path, char * (*f)(const char *, int)){
	split_path_t p;
	const char * end = f(path + 1, '/');
	const char * pad = path + ('/' == *path);
	if(!end){
		size_t size = strlen(pad);
		p.end = calloc(1, size + 1);
		strncpy(p.end, pad, size);
		p.string = NULL;
	}else{
		p.string = calloc(1, end - pad + 1);
		strncpy(p.string, pad, end - pad);
		const size_t size = strlen(end);
		p.end = calloc(1, size + 1);
		strncpy(p.end, end + 1,size);
	}
	return p;
}

group_t * walk(group_t * group, const char *path){
	if(!path) return NULL;

	split_path_t sp = split_path(path, strchr);
	ssize_t pos = get(&group->inode, sp.string ? sp.string : sp.end);
	if(0 > pos){
		free(sp.string);
		free(sp.end);
		return NULL;
	}
	group_t * g = struct_read(group->inode.file_ptr.file, pos, *g);
	if(sp.string){
		group = walk(g,sp.end);
		free(g);
	} else{
		group = g;
	}
	free(sp.string);
	free(sp.end);
	return group;
}


int lfs_getattr( const char *path, struct stat *stbuf ) {
	int res = 0;
	group_t * root = struct_read(file_system, 0, *root);

	memset(stbuf, 0, sizeof(struct stat));
	if( strcmp( path, "/" ) == 0 ) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else  {
		group_t * group = walk(root,path);
		if( group ){
			stbuf->st_mode = group->type | 0777;
			stbuf->st_nlink = 2;
			if( S_IFREG == group ->type) {
				stbuf->st_nlink = 1;
				file_ptr * fp = &group->inode.file_ptr;
				file_t * file =  struct_read(fp->file, fp->pos, *file);
				stbuf->st_size = file->size;
				stbuf->st_atime = file->access_time;
				stbuf->st_mtime = file->modfication_time;
			}
			free(group);
		}else{
			res = -ENOENT;
		}
	}
	free(root);
	return res;
}


void lfs_list_dir(inode_t * node, void *buf, fuse_fill_dir_t filler){
	if(node->level){
		for (size_t i = 0; i < node->fill; i++) {
			inode_t * n = (inode_t*)buf_read(
				node->file_ptr.file,
				node->values[i],
				node->file_ptr.size
			);
			lfs_list_dir(n,buf,filler);
			free(n);
		}
	}else{
		for (size_t i = 0; i < node->fill; i++) {
			file_ptr * string = get_string(node->file_ptr.file, node->keys[i]);
			printf("string(%lu) = %s\n",node->keys[i], string->data );
			filler(buf,string->data,NULL,0);
			free(string);
		}
	}
}

int lfs_readdir( const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi ) {

	printf("readdir: (path=%s)\n", path);
	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	group_t * root = (group_t *)buf_read(file_system, 0, sizeof(group_t) - sizeof(file_ptr));
	group_t * node = walk(root,path);
	if(node){
		lfs_list_dir(&node->inode,buf,filler);
		free(node);
	} else{
		lfs_list_dir(&root->inode,buf,filler);
	}
	free(root);
	return 0;
}

int lfs_mknod( const char * path, mode_t mode, dev_t dev){
	group_t * root = struct_read(file_system, 0, *root );
	split_path_t sp = split_path(path,strrchr);
	group_t * spot = walk(root,sp.string);
	if(spot){
		free(root);
		root = spot;
	}
	file_t file = {
		.group.type = S_IFREG,
		.size = 0,
		.access_time = time(NULL),
		.modfication_time = time(NULL)
	};
	struct_add_fptr(&root->inode, sp.end, file);
	free(sp.string);
	free(sp.end);
	return 0;
}

int lfs_mkdir( const char * path, mode_t mode){
	group_t * root = struct_read(file_system, 0, *root);
	split_path_t sp = split_path(path, strrchr);
	group_t * spot = walk(root, sp.string);
	if(spot){
		free(root);
		root = spot;
	}
	group_t group = {.type = S_IFDIR};

	struct_add_fptr(&root->inode, sp.end, group);
	free(root);
	free(sp.string);
	free(sp.end);
	return 0;
}
int lfs_unlink(const char * path){
	group_t * root = (group_t *)buf_read(file_system, 0, sizeof(group_t) - sizeof(file_ptr));
	split_path_t sp = split_path(path,strrchr);
	group_t * spot = walk(root,sp.string);
	if(spot){
		free(root);
		root = spot;
	}
	delete(&root->inode,sp.end);
	free(sp.string);
	free(sp.end);
	return 0;
}

int lfs_rmdir( const char * path){
	group_t * root = (group_t *)buf_read(file_system, 0, sizeof(group_t) - sizeof(file_ptr));
	split_path_t sp = split_path(path,strrchr);
	group_t * spot = walk(root,sp.string);
	if(spot){
		free(root);
		root = spot;
	}
	delete(&root->inode,sp.end);
	free(sp.string);
	free(sp.end);
	return 0;
}

int lfs_open( const char *path, struct fuse_file_info *fi ) {
  return 0;
}

char * hash(size_t key){
	char *string = calloc(1,9);
	sprintf(string,"%08x", (unsigned int)key);
	return string;
}

page_t * merge_page(inode_t ** node, size_t key){
	char * key_hash = hash(key);
	ssize_t pos = get(*node, key_hash);
	if(0 > pos){
		static page_t p;
		*node = struct_add(*node, key_hash, p);
		pos = get(*node, key_hash);
	}
	free(key_hash);
	return struct_read((*node)->file_ptr.file, pos, page_t);
}

int lfs_read( const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi ) {
	group_t * root = struct_read(file_system, 0, *root);
	group_t * spot = walk(root,path);
	free(root);
	file_ptr *fp = &spot->inode.file_ptr;
	file_t * file = struct_read( fp->file, fp->pos,*file );
	free(spot);

	const size_t start = offset, end = start + size;
	while(offset < end) {
		const off_t local_offset = offset % sizeof(page_t);
		const size_t local_size = min(end - offset, sizeof(page_t) - local_offset);

		inode_t * node = &file->group.inode;
		page_t * page = merge_page(&node, offset / sizeof(page_t) );
		memcpy(offset - start + buf, page->page + local_offset, local_size);
		offset += local_size;
		free(page);
	}
	file->access_time = time(NULL);
	struct_write(file);
  return size;
}

int lfs_write( const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
	group_t * root = struct_read(file_system, 0, *root);
	group_t * spot = walk(root,path);
	free(root);
	file_ptr *fp = &spot->inode.file_ptr;
	file_t * file = struct_read( fp->file, fp->pos,*file );
	free(spot);

	const size_t start = offset, end = start + size;
	while(offset < end) {
		const off_t local_offset = offset % sizeof(page_t);
		const size_t local_size = min(end - offset, sizeof(page_t) - local_offset);

		inode_t * node = &file->group.inode;
		page_t * page = merge_page(&node, offset / sizeof(page_t) );
		memcpy(page->page + local_offset, offset - start +  buf ,local_size);

		offset += local_size;
		file->size += local_size;

		struct_write(page);
		free(page);
	}
	file->modfication_time = time(NULL);
	struct_write(file);
	return size;
}

int lfs_release(const char *path, struct fuse_file_info *fi) {
	return 0;
}

int lfs_utime( const char * path, struct utimbuf *buf){
	return 0;
}

FILE * merge(char * file, char * mode){
  FILE * fp = fopen(file,mode);
  if(!fp) {
    fp = fopen(file,"w");
    fclose(fp);
    fp = fopen(file,mode);
  }
  return fp;
}

int main( int argc, char *argv[] ) {
	init_printf_inode_extension();
	file_system = merge("filesystem.fs","r+b");
	size_t size = sizeof(group_t) - sizeof(file_ptr);
	group_t * root = (group_t *)buf_read( file_system, 0, size);
	if(!root){
		printf("No root!\n");
		group_t empty = {.type = S_IFDIR};

		root = struct_append(file_system, empty);
	}
	printf("%B\n", root );
	fuse_main( argc, argv, &lfs_oper );
	return 0;
}
