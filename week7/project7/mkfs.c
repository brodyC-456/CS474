#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "block.h"

#define FREE_BLOCK_MAP 2

void mkfs(void){
    // Allocate first 7 blocks
    // first 7 bits allocated -> 0111 1111 -> 127, 127 in hex is 7f, write 7f into free block map
    unsigned char block = 0x7f;
    bwrite(FREE_BLOCK_MAP, &block);
}