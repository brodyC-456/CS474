#include <stdio.h>
#include <stdlib.h>


void grow_stack(int n){
    if (n == 0){
        return;
    }

    int local = 1;
    printf("Stack: %p\n", (void *)&local);

    grow_stack(n - 1);
}

int main(){
    for (int i = 0; i < 5; i++){
        int *heap = (int*)malloc(sizeof(int)); 
        printf("Heap: %p\n", heap);
    }

    grow_stack(5);
    
}

/** 
 Output:
    Heap: 0x62b6fd7272a0
    Heap: 0x62b6fd7276d0
    Heap: 0x62b6fd7276f0
    Heap: 0x62b6fd727710
    Heap: 0x62b6fd727730
    Stack: 0x7ffff6eb9bf4
    Stack: 0x7ffff6eb9bc4
    Stack: 0x7ffff6eb9b94
    Stack: 0x7ffff6eb9b64
    Stack: 0x7ffff6eb9b34
*/