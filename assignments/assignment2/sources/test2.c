#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "arch/x86/include/generated/uapi/asm/unistd_64.h"

int main(int argc, char const *argv[]) {

  if(argc < 2) return 0;
  
  int error, length;
  do {
    error = syscall(__NR_length,&length); // Wait for message.
  } while(error);

  char * msg = malloc(length);
  syscall(__NR_get, msg, length); // Retrive message.
  printf("Recived message : %s\n", msg);

  printf("Sending message : %s\n", argv[1]);
  syscall(__NR_put, argv[1], strlen(argv[1])); // Send message.

  return 0;
}
