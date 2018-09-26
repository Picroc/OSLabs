#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int isExec = 1;

void handlerInt(int nothing){
	printf(" >KbIK\n");
}

void handlerQuit(int nothing){
	printf(" >Goodbye!\n");
	isExec = 0;
}

int main(){
	printf("Welcome! Press Ctrl+C to see the best Russian word and Ctrl+\\ to quit\n");

	signal(SIGINT, handlerInt);
	signal(SIGQUIT, handlerQuit);

	while(isExec){

	}

	exit(EXIT_SUCCESS);
}
