#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	pid_t cpid[2];

	int pipefd[2];

	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid[0] = fork();

	if(cpid[0] == 0){
		pid_t sc_pid = -1;

		close(pipefd[1]);
		read(pipefd[0], &sc_pid, sizeof(pid_t));
		close(pipefd[0]);

		printf("PID of the second child has been read\n");

		sleep(4);
		printf("Pausing the second child\n");

		kill(sc_pid, SIGSTOP);
	} else {
		cpid[1] = fork();
		if(cpid[1] == 0){
			while(1){
				printf("Second child is running...\n");
				sleep(1);
			}
		} else {
			close(pipefd[0]);
			write(pipefd[1], &cpid[1], sizeof(pid_t));
			close(pipefd[1]);

			printf("The PID of the second child has been written\n");

			//int wstatus = -1;
			waitpid(cpid[1], NULL, 0);

			exit(EXIT_SUCCESS);
		}
	}
}
