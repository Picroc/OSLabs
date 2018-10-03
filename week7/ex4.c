#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ARR_SIZE 10

void print_array(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}

	printf("\n");
}

void* m_realloc(void* target, size_t old_size, size_t new_size){
	if(target == NULL){
		void* block = malloc(new_size);
		return block;
	}
	if(new_size == 0){
		free(target);
		return target;
	}
	if(new_size == old_size){
		return target;
	}

	size_t size = sizeof(target);
	void* new_block = malloc(size * new_size);

	if(new_block){
		new_block = memcpy(new_block, target, size * fmin(old_size, new_size));
		free(target);
		return new_block;
	} else {
		return NULL;
	}
}

int main(){
	int* ar = malloc(sizeof(int) * ARR_SIZE);
	printf("Initial array: ");
	for(int i = 0; i < ARR_SIZE; i++){
		ar[i] = i;
		printf("%d ", ar[i]);
	}

	printf("\n\nAfter extending: ");

	ar = m_realloc(ar, ARR_SIZE, ARR_SIZE + 5);
	print_array(ar, ARR_SIZE+5);

	printf("\nAfter shrinking: ");

	ar = m_realloc(ar, ARR_SIZE + 5, 3);
	print_array(ar, 3);

	printf("\nAfter using 0 as a size (showing 20 elements): ");

	ar = m_realloc(ar, 3, 0);
	print_array(ar, 20);

	printf("\nAfter using NULL as ptr: ");

	ar = m_realloc(NULL, 0, 10);
	print_array(ar, 10);

	return 0;
}
