#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

const int SIZE=1024;  // bytes

struct bicycle {
    int wheel_count;
    char name[32];
};

int main(void)
{
    // Allocate some space from the OS
    void *heap = mmap(NULL, SIZE, PROT_READ|PROT_WRITE,
                  MAP_ANON|MAP_PRIVATE, -1, 0);

    // Challenge 1:
    //
    // Treat heap as an array of chars
    // Store a string there with strcpy() and print it

    char *p = (char *)heap;
    strcpy(p, "hello");
    printf("%s\n", p);

    // Challenge 2:
    //
    // Treat heap as an array of ints
    // Use a loop to store the values 0, 10, 20, 30, 40 in it
    // Use a loop to retrieve the value and print them
    int *ints = (int *)heap;

    for (int i = 0; i < 5; i++){
        ints[i] = i * 10;
    }

    for(int i = 0; i < 5; i++){
        printf("%d\n", ints[i]);
    }

    // Challenge 3:
    //
    // Treat heap as an array of struct bicycles
    // Store 3 bicycles
    // Print out the bicycle data in a loop
    struct bicycle *b = (struct bicycle *)heap;

    for (int i = 0; i < 4; i++){
        b[i].wheel_count = 2;
        sprintf(b[i].name, "bike %d", i);
    }

    for (int i = 0; i < 4; i++){
        printf("bike name: %s\n", b[i].name);
        printf("wheel count: %d\n", b[i].wheel_count);
        
    }

    // Challenge 4:
    //
    // If you used pointer notation, redo challenges 1-3 with array
    // notation, and vice versa.

    // Challenge 1 (the same)
    char *p1 = (char *)heap;
    strcpy(p1, "hello");
    printf("%s\n", p1);

    // Challenge 2

    int *ints1 = (int *)heap;

    for (int i = 0; i < 5; i++){
        *(ints1 + i) = i * 10;
    }

    for(int i = 0; i < 5; i++){
        printf("%d\n", *(ints1 + i));
    }

    // Challenge 3

    struct bicycle *b1 = (struct bicycle *)heap;

    for (int i = 0; i < 4; i++){
        (*(b1 + i)).wheel_count = 2;
        sprintf((*(b1 + i)).name, "bike %d", i);
    }

    for (int i = 0; i < 4; i++){
        printf("bike name: %s\n", (*(b1 + i)).name);
        printf("wheel count: %d\n", (*(b1 + i)).wheel_count);
        
    }




    // Challenge 5:
    //
    // Make the first 32 bytes of the heap a string (array of chars),
    // and follow that directly with an array of ints.
    //
    // Store a short string in the string area of the heap
    // Use a loop to store the values 0, 10, 20, 30, 40 in the int array
    // Use a loop to retrieve the value and print them
    // Print the string

    char *s = (char *)heap;
    int *nums = (int *)((char *)heap + 32);

    strcpy(s, "hello world");

    for (int i = 0; i < 5; i++){
        nums[i] = i * 10;
    }

    for (int i = 0; i < 5; i++){
        printf("%d\n", nums[i]);
    }
    printf("%s\n", s);

    // Challenge 6:
    //
    // Make an array of interleaved `struct bicycle` and `int` data
    // types.
    //
    // The first entry in the heap will be a `struct bicycle`, then
    // right after that, an `int`, then right after that a `struct
    // bicycle`, then an `int`, etc.
    //
    // Store as many of these as can fit in SIZE bytes. Loop through,
    // filling them up with programmatically-generated data. Then loop
    // through again and print out the elements.

    struct bicycle *bi;
    int *val;

    int pair_size = sizeof(struct bicycle) + sizeof(int);
    int count = SIZE / pair_size;

    for (int i = 0; i < count; i++){
        bi = (struct bicycle *)((char *)heap + i * pair_size);
        val = (int *)((char *)bi + sizeof(struct bicycle));

        bi->wheel_count = 2;
        sprintf(bi->name, "bike %d", i);
        *val = i;
    }

    for(int i = 0; i < count; i++){
        bi = (struct bicycle *)((char *)heap + i * pair_size);
        val = (int *)((char *)bi + sizeof(struct bicycle));

        printf("%s (%d wheels), %d\n", bi->name, bi->wheel_count, *val);
    }



    // Free it up
    munmap(heap, SIZE);
}