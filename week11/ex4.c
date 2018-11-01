#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fin = open("ex1.txt", O_RDONLY);
    int fout = open("ex1.memcpy.txt", O_RDWR | O_CREAT | O_TRUNC);

    struct stat statbuf;
    void *dest, *src;

    if( fstat(fin, &statbuf) < 0){
        printf("fstat failure\n");
        exit(1);
    }

    //lseek(fout, statbuf.st_size - 1, SEEK_SET);
    //write(fout, "", 1);
    ftruncate(fout, statbuf.st_size);

    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fin, 0);
    dest = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fout, 0);

    memcpy(dest, src, statbuf.st_size);

    fchmod(fout, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    exit(0);
}