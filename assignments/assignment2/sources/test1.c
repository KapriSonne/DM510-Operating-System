#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "arch/x86/include/generated/uapi/asm/unistd_64.h"

int main(int argc, char const *argv[]) {

  if(argc < 2) return 0;
  printf("Sending message : %s\n", argv[1]);
  syscall(__NR_put, argv[1], strlen(argv[1])); // Send message.

  sleep(1);

  int length;
  syscall(__NR_length,&length); // Get length of message.
  char * msg = malloc(length); 
  syscall(__NR_get, msg, length); // Retive message;
  printf("Recived message : %s\n", msg);
  free(msg); 

  return 0;
}
