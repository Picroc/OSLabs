#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    int rand = open("/dev/random", O_RDONLY);
    if (rand < 0){
        printf("Error\n");
    } else {
        char string[20];
        ssize_t res = read(rand, string, sizeof(string));
        if(res < 0){
            printf("Error 2\n");
        } else {
            FILE *fout = fopen("ex1.txt", "w+");
            fprintf(fout, "%s", string);
            fclose(fout);
        }
    }
}