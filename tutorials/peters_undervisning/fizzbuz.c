#include <stdio.h>

int main(){

int lower = 1;
int upper = 100;
  for (int i = lower; i < upper; i++) {
    if (i%3==0) printf("%s\n","fizz");
    if (i%5==0) printf("%s\n","buzz");
    if (i%3||i%5) printf("%s\n","fizz buzz");
  }

  int size = 5;
  int myArray[5] = {1,2,3,4,5};

  for (int i = 0; i<size; i++){
    int villy_has_aids = myArray[i];
    printf("myArray index #%d = %d\n",i,villy_has_aids);
  }


  return 0;
}
