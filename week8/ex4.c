#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define MB_10 1024*1024*10

int main(){
    struct rusage* usage = malloc(sizeof(struct rusage));
    for(int i = 0; i < 10; i++){
        int *ptr = malloc(MB_10);
        memset(ptr, 0, MB_10);
        getrusage(RUSAGE_SELF, usage);
        printf("%ld kb [%ld MB]\n", usage->ru_maxrss, usage->ru_maxrss / 1024);
        sleep(1);
    }
}