#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char* argv[]){
	int pipefd[2];
	char *buf = malloc(sizeof(char)*BUFFER_SIZE);

	if(argc != 2){
		fprintf(stderr, "Usage: ex1 <string>\n");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	printf("Strings before the pipe():\nStr1: %s\nStr2: %s\n", argv[1], buf);


	write(pipefd[1], argv[1], strlen(argv[1])+1);
	close(pipefd[1]);
	//printf("Just check...\n");
	read(pipefd[0], buf, BUFFER_SIZE);
	//printf("Just check...\n");

	printf("Strings after the pipe():\nStr1: %s\nStr2: %s\n", argv[1], buf);

	close(pipefd[0]);

	exit(EXIT_SUCCESS);

}
