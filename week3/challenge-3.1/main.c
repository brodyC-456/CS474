#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

const int SIZE=1024;  // bytes

struct firework {
    int shell_caliber;
    float lift_charge;
    float burst_charge;
    int fuse_delay_ms;
};

int main(void)
{
    // Allocate some space from the OS
    void *heap = mmap(NULL, SIZE, PROT_READ|PROT_WRITE,
                      MAP_ANON|MAP_PRIVATE, -1, 0);

    // Challenge: Store your favorite letter at the byte `heap` points
    // to, then print it with `%c` and also with `%d`.
    // TODO
    char *p = (char *)heap;
    *p = 'X';

    printf("%c\n", *p);
    printf("%d\n", *p);
    

    // Challenge: Store a string at the byte `heap` points to, then
    // print it.
    // TODO
    char *s = (char *)heap;
    strcpy(s, "hi im brody");
    printf("%s\n", s);

    // Challenge: Store an integer at the byte `heap` points to, then
    // print it.
    // TODO
    int *i = (int *)heap;
    *i = 28;
    printf("%d\n", *i);


    // Challenge: Store a float right *after* the int you just stored.
    // Print them both.
    // TODO
    float *f = (float *)((char *)heap + sizeof(int));
    *f = 3.52;
    printf("%d, %f\n", *i, *f);

    // Challenge: Store a short (a smallish integer) at byte offset 512
    // in the `heap` area. Then print it with `%d`, along with the int
    // and float you already stored.
    // TODO
    short *sh = (short *)((char*)heap + 512);
    *sh = 2;
    printf("%d, %f, %d\n", *i, *f, *sh);

    // Challenge: Store a struct firework at byte offset 48 in the
    // `heap` area. Make a `struct firework *` initialized to the right
    // position, then fill it with data (with the `->` operator). Then
    // print out the data, and also print out the int, float, and short
    // from above.
    // TODO
    struct firework *fw = (struct firework *)((char *)heap + 48);
    fw->shell_caliber = 23;
    fw->lift_charge = 1.2;
    fw->burst_charge = 10.4;
    fw->fuse_delay_ms = 10000;

    printf("%d, %f, %d\n", *i, *f, *sh);
    printf("Shell caliber: %d\n", fw->shell_caliber);
    printf("Lift charge: %.2f\n", fw->lift_charge);
    printf("Burst charge: %.2f\n", fw->burst_charge);
    printf("Fuse delay: %d ms\n", fw->fuse_delay_ms);

    // Challenge: Store a second struct firework directly after the
    // first one. Initialize and print.
    // TODO
    struct firework *fw2 = (struct firework *)((char *)heap + 48 + sizeof(*fw));

    fw2->shell_caliber = 80;
    fw2->lift_charge = 3.5;
    fw2->burst_charge = 36.3;
    fw2->fuse_delay_ms = 30000;

    printf("%d, %f, %d\n", *i, *f, *sh);
    printf("Shell caliber: %d\n", fw->shell_caliber);
    printf("Lift charge: %.2f\n", fw->lift_charge);
    printf("Burst charge: %.2f\n", fw->burst_charge);
    printf("Fuse delay: %d ms\n", fw->fuse_delay_ms);
    
    printf("Shell caliber: %d\n", fw2->shell_caliber);
    printf("Lift charge: %.2f\n", fw2->lift_charge);
    printf("Burst charge: %.2f\n", fw2->burst_charge);
    printf("Fuse delay: %d ms\n", fw2->fuse_delay_ms);
}