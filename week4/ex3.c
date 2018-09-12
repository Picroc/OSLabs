#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

char *request_command(char *buffer){
	printf("> ");
	scanf("%s", buffer);
	return buffer;
}

int main(){
	char buffer[20];
	while(1){
		system(request_command(buffer));
	}
	return 0;
}
