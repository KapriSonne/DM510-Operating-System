#include <stdio.h>

int main(){

  FILE *fp;

  // lets write to a file
  fp = fopen("write.txt", "w");
  fprintf(fp, "Testing... yo!\nheh.. meehh");

  // close the file
  fclose(fp);

  // lets read the file
  char buff[255];
  fp = fopen("write.txt", "r");

  // reads only first word, because it ends when encountered a space
  fscanf(fp, "%s", buff);
  printf("1: %s\n", buff);

  // reads remaining line til encountered with end of line
  fgets(buff, 255, (FILE*)fp);
  printf("2: %s\n", buff );

  // reads line completely
  fgets(buff, 255, (FILE*)fp);
  printf("3: %s\n", buff );

  // close the file
  fclose(fp);


// ---------------------------------------------------------
// lets read a file character by character
  char ch;
  fp = fopen("write.txt", "r");
  printf("\n");

  while (1){
    ch = fgetc(fp);
    if (ch==EOF){
      break;
    }
    printf("%c",ch);
  }
  printf("\n");
  return 0;

  //close the file
  fclose(fp);
}
