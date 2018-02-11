#include <stdio.h>

int main(){

  FILE *fp;

  // lets write to a file
  fp=fopen("write.txt", "w");
  fprintf(fp, "Testing...\nheh");

  int fgetc (FILE *fp);
  printf("%p\n",*fp);

  return 0;
}
