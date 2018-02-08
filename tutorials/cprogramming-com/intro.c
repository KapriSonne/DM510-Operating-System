// include is the "preprocessor" directive which tells the compiler to put
// code from the header
#include <stdio.h>
int main()
{
    int number;

    printf("Write a number: ");
    scanf("%d", &number);
    printf("You entered: %d\n", number);
    getchar();
    return 0;
}
