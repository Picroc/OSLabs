#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int isExec = 1;

void handlerKill(int nothing){
	printf(" >KbIK\n");
}

void handlerStop(int nothing){
	printf(" >8======B\n");
}

void handlerUsr1(int nothing){
	printf("Hello from Usr1\n");
	isExec = 0;
}

int main(){
	signal(SIGKILL, handlerKill);
	signal(SIGSTOP, handlerStop);
	signal(SIGUSR1, handlerUsr1);

	while(isExec){

	}

	exit(EXIT_SUCCESS);
}
