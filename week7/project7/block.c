#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "image.h"
#include "free.h"

#define BLOCK_SIZE 4096
#define FREE_BLOCK_MAP 2

// Reads content from a file into a buffer and returns said buffer
unsigned char *bread(int block_num, unsigned char *block){

    int block_location = BLOCK_SIZE * block_num;

    // if file doesnt exist, stop
    if(image_fd == -1){
        perror("Cannot find file");
        return NULL;
    }

    lseek(image_fd, block_location, SEEK_SET);
    read(image_fd, block, BLOCK_SIZE);
    return block;

}

// Writes the content of a buffer into a block
void bwrite(int block_num, unsigned char* block){
    
    int block_location = BLOCK_SIZE * block_num;

    if(image_fd == -1){
        perror("Cannot find file");
        return;
    }

    lseek(image_fd, block_location, SEEK_SET);
    write(image_fd, block, BLOCK_SIZE);

}

// Allocates a data block
int alloc(void){
    unsigned char free_map[BLOCK_SIZE];
    bread(FREE_BLOCK_MAP, free_map);
    int first_free_bit = find_free(free_map);
    if(first_free_bit == 0){
        return -1;
    }
    set_free(free_map, first_free_bit, 1);
    bwrite(FREE_BLOCK_MAP, free_map);
    return first_free_bit;
}