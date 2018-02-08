#include <stdio.h>

int main()
{
    int y = 0;
    int x;
    /* The loop goes while x < 10, and x increases by one every loop*/
    for ( x = 0; x < 10; x++ ) {
        /* Keep in mind that the loop condition checks
           the conditional statement before it loops again.
           consequently, when x equals 10 the loop breaks.
           x is updated before the condition is checked. */
        printf( "%d\n", x );
    }
    printf("\n");
    while (y < 10){
      printf("%d\n",y );
      y++;
    }
}
