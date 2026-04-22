#include <stdio.h>
#include <stdlib.h>


int global = 1;

int main(){

    int local = 1;
    int *heap = (int*)malloc(sizeof(int)); 
    printf("Stack: %p\n", (void *)&local);
    printf("Heap: %p\n", heap);
    printf("Global: %p\n", (void *)&global);
    printf("Main: %p\n", (void *)&main);
}

/** 
 Output:
    Stack: 0x7ffc4cebfc4c
    Heap: 0x645779c822a0
    Global: 0x64574c186010
    Main: 0x64574c183189
*/