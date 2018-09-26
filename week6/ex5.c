#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int isExec = 1;
pid_t cpid = -1;

void handlerUsr1(int nothing){
	printf("Child terminated!\n");
	isExec = 0;
}

int main(){
	cpid = fork();

	if(cpid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(cpid == 0){
		signal(SIGTERM, handlerUsr1);

		while(isExec){
			printf("I am alive!\n");
			sleep(1);
		}
	} else {
		sleep(10);
		kill(cpid, SIGTERM);
	}


	exit(EXIT_SUCCESS);
}
