#include <stdio.h>
#include <stdlib.h>

void usage(){
    puts("Usage: a2po page offset");
    perror(0);
}

int main(int argc, char *argv[]){

    if (argc > 3){
        usage();
    }
    int page = atoi(argv[1]);
    int offset = atoi(argv[2]);

    int address = page << 8;
    address = address | offset;

    printf("Page %i, Offset %i = Address %i\n", page, offset, address);



}