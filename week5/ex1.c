#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * PrintHello(void* arg){
	printf("Hello from thread %lld - I was created in iter %d.\n",
			(long long) pthread_self(), *(int*)arg);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	if(argv[1]){
		int n = atoi(argv[1]);
		pthread_t x;

		int rc, i;
		for(i = 0; i < n; i++){
			rc = pthread_create(&x, NULL, PrintHello, &i);
			if(rc){
				printf("\n ERROR: return code from pthread is %d \n", rc);
				exit(1);
			}
			printf("\n I am thread %d. Created new thread (%lld) in iteration %d\n",
					(int) pthread_self(), (long long) x, i);
		}
		pthread_exit(NULL);
	} else {
		printf("Wrong usage.\n");
		return 1;
	}
}
