#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MB_10 1024*1024*10

int main(){
    for(int i = 0; i < 10; i++){
        int *ptr = malloc(MB_10);
        memset(ptr, 0, MB_10);
        sleep(1);
    }
}