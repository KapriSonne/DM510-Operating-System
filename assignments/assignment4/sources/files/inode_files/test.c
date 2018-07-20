#include "inode.h"
#include <string.h>
#include <unistd.h>
#include <stddef.h>

FILE * merge(char * file, char * mode){
  FILE * fp = fopen(file,mode);
  if(!fp) {
    fp = fopen(file,"w");
    fclose(fp);
    fp = fopen(file,mode);
  }
  return fp;
}

int main(int argc, char const *argv[]) {
  init_printf_inode_extension();

  FILE * fp = merge("Hello.txt","r+b");
  setbuf(fp, NULL);
  char buffer [100];
  char msg[] = "my name";

  size_t size = sizeof(inode_t) - sizeof(file_ptr);
  inode_t * root = (inode_t *)buf_read(fp, 0, size);
  if(!root){
    printf("No root!\n");
    inode_t empty = {};
    root = (inode_t *)append(fp,size,empty.file_ptr.data);
  }
  size_t i = 0;
  for (; i < 10; i++) {
    sprintf(buffer,"hello %lu",i);
    printf("I = %lu\n",i );
    const inode_t * node = add(root, buffer, strlen(msg) + 1, msg);
    if(node != root){
      free(root);
    }
    root = node;
  }
  sprintf(buffer,"hello %d", i);
  printf("Deleting %s\n", buffer );
  ssize_t r = get(root,buffer);
  printf("Return = %ld\n", r);
  if(0 > r){
    printf("Key %s not found!\n", buffer );
  }
  printf("Tree = \n%B\n",root );
  free(root);
  fclose(fp);

  return 0;
}
