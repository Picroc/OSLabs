#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int n;
	if(fork()==0){
		n = getpid();
		printf("Hello from Child [PID - %d]\n", n);
	} else {
		n = getpid();
		printf("Hello from Parent [PID - %d]\n", n);
	}
	return 0;
}
