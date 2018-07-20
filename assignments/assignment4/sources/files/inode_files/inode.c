#include "inode.h"
#include <string.h>
#include <printf.h>



void print_key(FILE *stream, const inode_t * bpt, size_t i){
  if(bpt->level){
    fprintf(stream, "%lu", bpt->keys[i] );
  } else {
    fprintf(stream, "(%lu)",bpt->keys[i] );
    if(bpt->keys[i]){
      file_ptr * string =  get_string(bpt->file_ptr.file,bpt->keys[i]) ;
      fprintf(stream, "%s", string->data );
      free(string);
    }
  }
}

int print_arginfo (const struct printf_info *info, size_t n, int *argtypes){
  /* We always take exactly one argument and this is a pointer to the
     structure.. */
  if (n > 0)
    argtypes[0] = PA_POINTER;
  return 1;
}

int print_inode(FILE *stream, const struct printf_info *info, const void *const *args){

  const inode_t * bpt = *((const inode_t **) (*args));
  int length = 0 ;
  size_t i;
  length += fprintf(stream, "%lu /%lu -> %lu : [",bpt->level,bpt->fill, bpt->file_ptr.pos );
  for (i = 0; i < INODE_SIZE - 1; i++) {
    print_key(stream, bpt, i);
    length += fprintf(stream, ", ");
  }
  print_key(stream, bpt,i);
  length += fprintf(stream, "], [%lu",bpt->values[0]);
  for (i = 1; i < INODE_SIZE + 1; i++) {
    length += fprintf(stream, ", %lu", bpt->values[i]);
  }
  length += fprintf(stream, "]");
  return length;
}

int print_bpr_recursive(FILE *stream, const inode_t * bpt, size_t index){
  const void *const arg = &bpt;
  int sum = print_inode(stream, NULL, &arg);
  if(!bpt->level) return sum;
  for (size_t i = 0; i < bpt->fill; i++) {
    inode_t * n = struct_read(bpt->file_ptr.file, bpt->values[i], *n);
    if(bpt->values[i]){
      sum += fprintf(stream, "\n%*s",(int)index + 1, " ");
      sum += print_bpr_recursive(stream, n, index + 1);
    }
    free(n);
  }
  return sum;
}

int print_bpr(FILE *stream, const struct printf_info *info, const void *const *args){
  const inode_t * bpt = *((const inode_t **) (*args));
  return print_bpr_recursive(stream,bpt,0);
}

void init_printf_inode_extension(){
  register_printf_function ('N', print_inode, print_arginfo);
  register_printf_function ('B', print_bpr, print_arginfo);
}

file_ptr * get_string(FILE *fp, size_t pos){
  size_t length = 1;
  fseek(fp,pos,SEEK_SET);
  while(fgetc(fp)) length++;
  return buf_read(fp,pos,length);
}

file_ptr * tree_key(inode_t *node){
  file_ptr * f;
  if(node->level){
    inode_t * n = struct_read(
      node->file_ptr.file,
      node->values[0],
      *n
    );
    f = tree_key(n);
    free(n);
  } else{
    f = get_string(
      node->file_ptr.file,
      node->keys[0]
    );
  }
  return f;
}

ssize_t match(inode_t * node, char * key){
  const size_t size = node->fill - (node->level > 0);
  size_t i = 0;
  for (; i < size; i++) {
    file_ptr * string = get_string(node->file_ptr.file, node->keys[i]);
    int cmp = strcmp(key,string->data);
    free(string);
    if(0 > cmp){
      return i;
    } else if(0 == cmp){
      return node->level ? i + 1 :  KEY_EXISTS;
    }
  }
  return i;
}

inode_t * split_inode(inode_t * src, long index){
  inode_t * dest = calloc(1,sizeof(*dest));
  const size_t fsize = src->fill / 2, csize=(src->fill + 1) / 2;
  size_t size = src->level ? 1 : 0;
  dest->fill = fsize;
  dest->file_ptr = src->file_ptr;
  dest->level = src->level;
  src->fill = csize;
  size_t type = sizeof(*src->keys);
  memcpy(dest->keys, src->keys + csize, (fsize - size) * type);
  memset(src->keys + fsize, 0 ,fsize * type);

  type = sizeof(*src->values);
  memcpy(dest->values, src->values + csize, (fsize ) * type);
  memset(src->values + csize, 0 ,fsize * type);
  return dest;
}

void node_make_room(inode_t * node,long index){
  size_t size = (node->fill - index - (node->level > 0)) * sizeof(*node->keys);
  memmove( node->keys + index + 1, node->keys + index, size);

  size = (node->fill - index) * sizeof(*node->values);
  memmove(node->values + index + 1, node->values + index, size);
}

inode_t * node_tree(FILE *fp, size_t level){
  inode_t n = {
    .file_ptr.size = sizeof(n) - sizeof(file_ptr),
    .level = level,
    .fill = level > 0
  };
  if(level){
     inode_t * result = node_tree(fp,level - 1);
     n.values[0] = result->file_ptr.pos;
     free(result);
  }
  return (inode_t *)append(fp, n.file_ptr.size, n.file_ptr.data);
}


inode_t * add_recursive(inode_t * node, file_ptr * key, file_ptr * value){
  inode_t * out_node = node, *new_node = NULL, *right_node = NULL;
  ssize_t index = match(node,key->data);
  int new_item = 0, split = 0;

  if(0 > index) return new_node;
  if(node->level){
    if(!node->values[index]){ // Make new inode tree.
      right_node = node_tree(node->file_ptr.file, node->level);
    }else {
      right_node = struct_read(
        node->file_ptr.file,
        node->values[index],
        *right_node
      );
    }
    value = (file_ptr*)add_recursive(right_node,key,value);
    free(right_node);
    if(value){ //Handle split.
      key = tree_key((inode_t*)value);
      split = INODE_SIZE < node->fill;
      new_item = 1;
    }
  } else {
    split = INODE_SIZE == node->fill;
    new_item = 1;
  }
  if(split){
    new_node = split_inode(node, index);
    append_file_ptr(&new_node->file_ptr); // Write the old node.
    buf_write(&node->file_ptr); // Write the new node.
    if(index > node->fill){
      out_node = new_node;
    }
  }
  if(!node->level || new_item){
    index = match(out_node,key->data);
    if(index < out_node->fill){
      node_make_room(out_node,index);
    }
    out_node->values[index + (node->level > 0)] = value->pos;
    out_node->fill++;
    out_node->keys[index] = key->pos;
  }
  struct_write(out_node);
  return new_node;
}

inode_t * add(inode_t * root, char * key, size_t value_size, void * value){
    return add_custom_key(root,strlen(key) + 1, key ,value_size,value);
}

inode_t * add_custom_key(inode_t * root, size_t key_size,  void * key, size_t value_size, void * value){
  if(!(root && key && value)) return NULL;
  size_t size = sizeof(inode_t) - sizeof(file_ptr);

  file_ptr * key_ptr = append(root->file_ptr.file, key_size, key);
  file_ptr * value_ptr = append(root->file_ptr.file, value_size, value);

  inode_t * right_root = add_recursive(root,key_ptr,value_ptr);
  if(right_root){  // Root got split.
    inode_t * new_root = (inode_t *)new_file_ptr(root->file_ptr.file,0,size,NULL);
    memset(new_root->file_ptr.data,0,size);
    key_ptr = tree_key(right_root);
    new_root->keys[0] = key_ptr->pos;
    new_root->file_ptr = root->file_ptr;
    append_file_ptr(&root->file_ptr);

    new_root->level = root->level + 1;
    new_root->values[0] = root->file_ptr.pos;
    new_root->values[1] = right_root->file_ptr.pos;
    new_root->fill = 2;

    buf_write((file_ptr*)new_root);
    free(right_root);
    root = new_root;
  }
  free(key_ptr);
  free(value_ptr);
  return root;
}

ssize_t find(inode_t * node, char * key){
  size_t i = 0;
  size_t size = node -> fill - (node->level > 0);
  for (; i < size; i++) {
    file_ptr * string = get_string(node->file_ptr.file, node->keys[i]);
    int cmp = strcmp(key,string->data);
    free(string);
    if((node->level && 0 > cmp) || (!node->level && !cmp)){
      return i;
    }
  }
  return node->level ? i : KEY_NOT_EXISTS;
}

ssize_t get(inode_t * node, char * key){
  ssize_t index = find(node,key);
  if(0 > index) {
    return index;
  }
  ssize_t pos = node->values[index];
  if(node->level && 0 <= pos){
    node = struct_read(node->file_ptr.file, pos, *node);
    pos = get(node,key);
    free(node);
  }
  return pos;
}

ssize_t delete(inode_t * node, char * key){
  ssize_t index = 0, pos = 0;
  index = find(node,key);
  pos = node->values[index];
  if(node->level && 0 <= pos){
    node = struct_read(node->file_ptr.file,pos,*node);
    pos = delete(node,key);
    free(node);
  } else if(0 <= index){
    memmove(
      node->keys + index,
      node->keys + index + 1,
      (node->fill - index - 1) * sizeof(*node->keys)
    );
    node->keys[node->fill - 1] = 0;
    memmove(
      node->values + index,
      node->values + index + 1,
      (node->fill - index - 1) * sizeof(*node->values)
    );
    node->values[node->fill - 1] = 0;
    node->fill--;
    buf_write(&node->file_ptr);
  } else{
    pos = -1;
  }
  return pos;
}
