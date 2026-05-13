#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "image.h"
#include "block.h"
#include "ctest.h"
#include "inode.h"
#include "free.h"
#include "mkfs.h"

#define BLOCK_SIZE 4096
#define INODE_FREE_MAP 1
#define BLOCK_FREE_MAP 2

int setup(){
    int fd = image_open("foo.txt", 1);
    mkfs();
    return fd;
}

void test_open_close(){
    int fd = image_open("foo.txt", 1);
    CTEST_ASSERT(fd != -1, "file not opened!");
    int closed = image_close();
    CTEST_ASSERT(closed != -1, "Closing file failed!");
}

void test_mkfs(){
    int fd = setup();
    unsigned char block[BLOCK_SIZE];
    bread(BLOCK_FREE_MAP, block);
    int free = find_free(block);
    CTEST_ASSERT(free == 7, "mkfs failed!");
    image_close();
}

void test_read_write(){
    
    int fd = setup();
    unsigned char block[BLOCK_SIZE] = "Hello, Blocks!";
    bwrite(7, block);
    unsigned char buf[BLOCK_SIZE];
    bread(7, buf);
    CTEST_ASSERT(memcmp(buf, "Hello, Blocks!", 15) == 0, "Read/Write failed!");
    image_close();
}

void test_ialloc(){
    int fd = setup();
    int inode_num = ialloc();

    // gunna test if this works by finding the next free bit then checking if its write after the one we just allocated
    unsigned char buf[BLOCK_SIZE];
    bread(INODE_FREE_MAP, buf);
    int free = find_free(buf);
    CTEST_ASSERT(free == inode_num + 1, "ialloc failed!");
    image_close();
}

void test_alloc(){
    int fd = setup();
    int block_num = alloc();

    // same as above
    unsigned char buf[BLOCK_SIZE];
    bread(BLOCK_FREE_MAP, buf);
    int free = find_free(buf);
    CTEST_ASSERT(free == block_num + 1, "alloc failed!");
    image_close();
}

int main(void){
    
    // Test if open/close works
    test_open_close();

    // Test if mkfs works
    test_mkfs();

    // Test if writing/reading works
    test_read_write();

    // The next two tests SHOULD prove that find_free and set_free work correctly...
    // Test if ialloc works
    test_ialloc();

    // Test if alloc works
    test_alloc();

    // Display results
    CTEST_RESULTS();
}