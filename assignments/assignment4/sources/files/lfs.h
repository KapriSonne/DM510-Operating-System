#ifndef DM510_LFS_H
#define DM510_LFS_H

#include <fuse.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

int lfs_getattr( const char *, struct stat * );
int lfs_readdir( const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info * );
int lfs_mknod( const char *, mode_t, dev_t);
int lfs_mkdir( const char *, mode_t);
int lfs_unlink(const char *);
int lfs_rmdir( const char *);

//int lfs_truncate( const char *, off_t, struct fuse_file_info *fi );
int lfs_open( const char *, struct fuse_file_info * );
int lfs_read( const char *, char *, size_t, off_t, struct fuse_file_info * );
int lfs_release(const char *path, struct fuse_file_info *fi);
int lfs_write( const char *, const char *, size_t, off_t, struct fuse_file_info *);
int lfs_utime( const char *, struct utimbuf *buf);

static struct fuse_operations lfs_oper = {
	.getattr	= lfs_getattr,
	.readdir	= lfs_readdir,
	.mknod = lfs_mknod,
	.mkdir = lfs_mkdir,
	.unlink = lfs_unlink,
	.rmdir = lfs_rmdir,
	.truncate = NULL,
	.open	= lfs_open,
	.read	= lfs_read,
	.release = lfs_release,
	.write = lfs_write,
	.rename = NULL,
	.utime = lfs_utime
};



#endif /* end of include guard: DM510_LFS_H */
