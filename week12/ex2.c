#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256

int main(){

    FILE* fout = fopen("ex2.txt", "w");

    char* buffer = malloc(sizeof(char) * BUF_SIZE);

    while(fgets(buffer, BUF_SIZE, stdin) != NULL){
        printf("%s", buffer);
        fprintf(fout, "%s", buffer);
    }

    printf("\n");
    fclose(fout);
}