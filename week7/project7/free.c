#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BITS_PER_BYTE 8
#define NUM_BYTES 4096

// finds the lowest unallocated bit in a byte
int find_low_clear_bit(unsigned char x)
{
    for (int i = 0; i < 8; i++)
        if (!(x & (1 << i)))
            return i;
    
    return -1;
}

void set_free(unsigned char *block, int num, int set){
    int byte_num = num / BITS_PER_BYTE;
    int bit_num = num % BITS_PER_BYTE;

    int byte_val = block[byte_num];
    int new_byte_val = 0b0;

    if (set == 1){
        new_byte_val = (0b1 << bit_num) | byte_val;
    }
    else if(set == 0){
        new_byte_val = (~(0b1 << bit_num) ) & byte_val;
    }

    block[byte_num] = new_byte_val;
}

int find_free(unsigned char *block){
    for(int i = 0; i < NUM_BYTES; i++){
        unsigned char curr_byte = block[i];
        int clear_bit_num = find_low_clear_bit(curr_byte);
        // If there are no free bits, continue, else return the location of the free bit
        if(clear_bit_num != -1) {
            return (i * BITS_PER_BYTE) + clear_bit_num;
        }
    }

    // If there are no free bits return -1
    return -1;
}