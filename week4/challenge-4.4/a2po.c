#include <stdio.h>
#include <stdlib.h>

void usage(){
    puts("Usage: a2po address");
    perror(0);
}

int main(int argc, char *argv[]){

    if (argc > 2){
        usage();
    }
    int address = atoi(argv[1]);

    unsigned int page = address >> 8;
    unsigned int off = address & 0b11111111;

    printf("Address %i = Page %i, Offset %i\n", address, page, off);



}