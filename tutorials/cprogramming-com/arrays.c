#include <stdio.h>

int main(){

  // single dimensional array
  char string_1[4];

  // multi dimensional array
  int string_2[8][8];

  // lets add some value to string_1
  string_1[0] = 'c';
  string_1[1] = 'a';
  string_1[2] = 'k';
  string_1[3] = 'e';

  // and string_2
  string_2[0][0] = 2;

  // important to notice that when we talk about arrays, we dont need
  // to make an reference operator '&' it is done automatically, e.g:

  char *ptr_1;
  char str[40];
  ptr_1 = str;      // Gives the memory address without '&'

  // opposed to:
  int *ptr_2;
  int num;
  ptr_2 = &num;     // Requires the '&' to give the memory address to the ptr

  // lets print string_1
  printf("%s\n",string_1);

  // lets access a single point in the array
  printf("%c\n",string_1[2]);

  return 0;
}
