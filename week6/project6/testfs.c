#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "image.h"
#include "block.h"
#include "ctest.h"

#define BLOCK_SIZE 4096

int main(void){
    
    // Test if open works
    int fd = image_open("foo.txt", 1);
    CTEST_ASSERT(fd != -1, "file not opened!");

    // Test if writing/reading works
    unsigned char block[BLOCK_SIZE] = "Hello, Blocks!";
    bwrite(7, block);
    unsigned char buf[BLOCK_SIZE];
    bread(7, buf);
    CTEST_ASSERT(memcmp(buf, "Hello, Blocks!", 15) == 0, "Read/Write failed!");
    
    // Test if closing works
    int closed = image_close();
    CTEST_ASSERT(closed != -1, "Closing file failed!");


    // Display results
    CTEST_RESULTS();
}