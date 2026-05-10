#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "image.h"

#define BLOCK_SIZE 4096

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