#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int image_fd = -1;

// Opens a file, creating it if it doesn't exist and truncating if specified
int image_open(char *filename, int truncate){
    image_fd = truncate ? open(filename, O_RDWR|O_CREAT|O_TRUNC, 0600) : open(filename, O_RDWR|O_CREAT, 0600);
    return image_fd;
}

// Closes the file
int image_close(void){
    return close(image_fd);
}