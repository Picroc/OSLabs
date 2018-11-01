#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fptr = open("ex1.txt", O_RDWR);

    char *str = "This is a nice day!";
    ftruncate(fptr, strlen(str));

    struct stat statbuf;
    void *map;

    if( fstat(fptr, &statbuf) < 0){
        printf("fstat failure\n");
        exit(1);
    }

    lseek(fptr, statbuf.st_size - 1, SEEK_SET);
    map = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fptr, 0);
    memcpy(map, str, strlen(str));
    sync();
    exit(0);
}