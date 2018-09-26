#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char* argv[]){
	int pipefd[2];
	pid_t cpid;
	char *buf = malloc(sizeof(char)*BUFFER_SIZE);

	if(argc != 2){
		fprintf(stderr, "Usage: ex1 <string>\n");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if(cpid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(cpid == 0){ //child process
		close(pipefd[1]);
		read(pipefd[0], buf, BUFFER_SIZE);
		printf("Read string: %s (Process %d)\n", buf, (int) getpid());
	} else {
		close(pipefd[0]);
		write(pipefd[1], argv[1], strlen(argv[1])+1);
		close(pipefd[1]);
		printf("Just a parent process output (Process %d)\n", (int) getpid());
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}
