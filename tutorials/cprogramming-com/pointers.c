#include <stdio.h>
#include <stdlib.h>

int main()
{
    // integer x is assigned 3 (x is stored on the stack)
    int x = 3;

    // pointer to integer p  (p is stored on the stack)
    int *p;

    // assign the address of x to p
    p = &x;

    printf("\nx = %d\n",x);
    printf("\nAddress for x: %p\n",&x );
    printf("\ndereference whats on that address:\n*p on &x => %d\n\n",*p); // dereferencing p (meaning see what at the pointers locating)

    // sets ptr to point to the start of our allocated memory
    // which has a size of int (typically 4 bytes on 32- and 64-bit systems)
    // the allocated memory cant be used by other programs, so its
    // important to free it again. (else we get memory leeks)
    // when we malloc we allocate in heap memory
    int *ptr = malloc(sizeof(int));

    // another and better way to archive the same
    // int *ptr = malloc(sizeof(*ptr));

    // we allocate another piece of memory
    int *ptr2 = malloc(sizeof(ptr2));

    // assign value to the two allocated memory chunks
    *ptr = 42;
    *ptr2 = 7;

    // lets free the memory again
    free(ptr);
    free(ptr2);
}
