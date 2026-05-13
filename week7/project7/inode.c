#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "block.h"
#include "free.h"

#define FREE_INODE_MAP 1
#define BLOCK_SIZE 4096


// Allocates an Inode
int ialloc(void){
    unsigned char inode_map[BLOCK_SIZE];
    bread(FREE_INODE_MAP, inode_map);
    int first_free_bit = find_free(inode_map);
    if (first_free_bit == -1){
        return -1;
    }
    set_free(inode_map, first_free_bit, 1);
    bwrite(FREE_INODE_MAP, inode_map);
    return first_free_bit;
}