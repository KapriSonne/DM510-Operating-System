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
    printf("\nAddress for x: %p\n",p);
    printf("\ndereference whats on that address:\n*p on &x => %d\n\n",*p); // dereferencing p (meaning see what at the pointers locating)

    // sets ptr to point to the start of our allocated memory (the address)
    // which has a size of int (typically 4 bytes on 32- and 64-bit systems)
    // the allocated memory cant be used by other programs, so its
    // important to free it again. (else we get memory leaks)
    // when we malloc we allocate in heap memory
    int *ptr = malloc(sizeof(int));

    printf("%p\n",ptr);

    // another and better way to archive the same
    // int *ptr = malloc(sizeof(*ptr));

    // we allocate another piece of memory
    int *ptr2 = malloc(sizeof(*ptr2));

    // assign the value '42' to the allocated memory starting from the address
    // in heap pointed by ptr
    *ptr = 42;

    // same ^
    *ptr2 = 7;

    // lets free the memory again
    free(ptr);
    free(ptr2);

    /* -----------------------------------------------------------
    // Pointer arithmetics: */

    // now we allocate an array in heap of size 5 times the size of int
    int *array = malloc(5*sizeof(*array));
    //           0  1  2  3  4
    // HEAP:    [ ][ ][ ][ ][ ]

    *array = 10;
    // HEAP:    [10][ ][ ][ ][ ]
    // Pointer:  ^

    // Now lets increment the pointer to point at the next integer in heap,
    // and assign the value '20'
    array++;
    *array = 20;
    // HEAP:    [10][20][ ][ ][ ]
    // Pointer:      ^

    // without incrementing the pointer, we assign current pointed
    // position + 2 (hence we got the 4th slot) the value 100.
    *(array + 2) = 100;
    // HEAP:    [10][20][ ][100][ ]
    // Pointer:      ^

    // but more readable to access it like an array.
    // however! - rememeber it counts from whereever the current pointer
    // is pointing. In this case, we assign 66 to the last element in array.
    array[3] = 66;
    // HEAP:    [10][20][ ][100][66]
    // Pointer:      ^

    // to free the memory, we need to reassign the pointer back to beginning
    // of our array. We know its at index 1, so:
    array--;
    free(array);
    // HEAP:    none
    // Pointer: none

    /* -----------------------------------------------------------
    // Multi dimension arrays pointer fun: */
    char **a;

    a=(char **) malloc(3*sizeof(char *));

    for(int i=0;i<3;i++){
      a[i]=(char *) malloc(3*sizeof(char));
    }

    // free the memory again
    for(int i=0;i<3;i++){
      free(a[i]);
    }
    free(a);
}
