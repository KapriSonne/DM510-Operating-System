/*
 - Deadline 1. assignment 28 februar 10AM.
 - lookup godbolt.org
 - To get the assembly version of c code: gcc -S program.c
 - To get the file created by the pre processor: gcc -E program.c | LESS -N
 - strace
 - char = 1 byte
 - char goes from [-128, .., 127]
 - int = usually 4 byte (32- and 64 bit maschines)
 - Debugger: ddd
 - Declaring is e.g: int i;
 - Assigning is e.g: int i = 1;
 - malloc dynamically allocates memory on the heap, but functions like: int ptr2[] = {1,2,3}
   allocates memory on the stack.
 - if ( x < 5 || x < 4)       second argument is never avaluated if e.g x = 3

TASK for next time:
      x = 5
      y = (x++) * (x++) * (x++)
*/
#include <stdio.h>
int main(){
  int x = 5;
  int y;
  y = (x++)*(x++)*(x++);
  printf("%i\n",y);
  return 0;
}
