#ifndef DM510_INODE_H
#define DM510_INODE_H
#include "file_ptr.h"
#define KEY_EXISTS -1
#define KEY_NOT_EXISTS -2
#define FULL_INODE -3
#define INODE_SIZE 4

typedef struct{
  file_ptr file_ptr;
  size_t level;
  size_t fill;
  size_t keys[INODE_SIZE];
  size_t values[1 + INODE_SIZE];
  char data[];
} inode_t;

//Initialise the N and B printf keywords.
void init_printf_inode_extension();

//Get a string from a given file and position
file_ptr * get_string(FILE *fs, size_t pos);

//Create a b+ tree of a given depth, OBS: only the left most part of the nodes are filled.
inode_t * node_tree(FILE *fs, size_t depth);

//Get the leftmost key of a given b+ tree.
file_ptr * tree_key(inode_t *);

//Add some data, with a key, to the given b+ tree. OBS: Should the root splt, the new root will returned from the function.
inode_t * add(inode_t *, char *, size_t, void *);

inode_t * add_custom_key(inode_t *,size_t, void *, size_t, void *);

//Get the data of a given key.
ssize_t get(inode_t * , char *);

//Delete a key and its accompanying data.
ssize_t delete(inode_t * , char *);

#define struct_add(node,key,st) add(node,key,sizeof(st),&st)
#define struct_add_fptr(node,key,st) add(node,key,sizeof(st) - sizeof(file_ptr), (char *)&st + sizeof(file_ptr))


#endif /* end of include guard: DM510_INODE_H */
