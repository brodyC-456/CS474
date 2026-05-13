#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int image_fd = -1;

// Opens a file, creating it if it doesn't exist and truncating if specified
int image_open(char *filename, int truncate){
    int flags = O_RDWR | O_CREAT | (truncate? O_TRUNC: 0);
    image_fd = open(filename, flags, 0600);
    return image_fd;
}

// Closes the file
int image_close(void){
    return close(image_fd);
}