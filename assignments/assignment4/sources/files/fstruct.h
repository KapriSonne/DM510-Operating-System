#ifndef DM510_FSTRUCT_H
#define DM510_FSTRUCT_H
#include <time.h>
#include "inode_files/inode.h"

typedef struct{
  inode_t inode;
  mode_t type;
  char data[];
} group_t;


typedef struct{
  group_t group;
  size_t size;
  time_t access_time;  /* Time of last access */
  time_t modfication_time;  /* Time of last modification */
} file_t;

typedef struct{
  file_ptr file_ptr;
  char page[1 << 12];
} page_t;

#endif /* end of include guard: DM510_FSTRUCT_H */
