#include <stdlib.h>
#include <stdio.h>

void print_array(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}

	printf("\n");
}

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage: ./ex2 <array size>\n");
		return -1;
	}

	int n = atoi(argv[1]);
	int *array = malloc(sizeof(int) * n);

	for(int i = 0; i < n; i++){
		array[i] = i;
	}

	print_array(array, n);
	free(array);

	return 0;
}
