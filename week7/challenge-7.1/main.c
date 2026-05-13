#include <stdio.h>

#define BITS_PER_BYTE 8

unsigned char bitmap[4096];

void print_byte(unsigned char b)
{
    if (b <= 1)
        printf("%d", b);

    else {
        print_byte(b >> 1);
        printf("%d", b & 1);
    }
}

void print_byte_n(unsigned char b)
{
    print_byte(b);
    putchar('\n');
}

int get_bit(int index)
{
    // TODO
    int byte_num = index / BITS_PER_BYTE;
    int bit_num = index % BITS_PER_BYTE;

    int bit = (bitmap[byte_num] >> bit_num) & 0b1;
    return bit;
    


}

void set_bit(int index, int value)
{
    int byte_num = index / BITS_PER_BYTE;
    int bit_num = index % BITS_PER_BYTE;

    int byte_val = bitmap[byte_num];
    int new_byte_val = 0b0;

    if (value == 1){
        new_byte_val = (0b1 << bit_num) | byte_val;
    }
    else if(value == 0){
        new_byte_val = (~(0b1 << bit_num) ) & byte_val;
    }

    bitmap[byte_num] = new_byte_val;


}

int main(void)
{
    set_bit(0,1);
    set_bit(2,1);
    set_bit(3,1);
    set_bit(4,1);
    set_bit(7,1);
    set_bit(8,1);
    

    print_byte_n(bitmap[0]);
    print_byte_n(bitmap[1]);

    for (int i = 0; i <= 9; i++) {
        printf("%d: %d\n", i, get_bit(i));
    }
}