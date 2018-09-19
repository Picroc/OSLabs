#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int *buffer;

void init(){
	buffer = malloc(sizeof(int) * BUFFER_SIZE);
}

int count = 0;
int show = 0;

//flags
int p_sleep = 0;
int c_sleep = 0;

int flag = 0; //0 - producer, 1 - consumer

void print_buffer(){
	for(int i = 0; i < BUFFER_SIZE; i++){
		printf("%d ", buffer[i]);
	}
	printf("\n");
}

void sleep_me_baby(){
	if(flag == 0){
		//printf("Producer sleep!\n");
		p_sleep = 1;
	} else {
		//printf("Consumer sleep!\n");
		c_sleep = 1;
	}
}

void wake_me_up(){ //wake me up inside
	if(flag == 0){
		//printf("Consumer wakes up!\n");
		c_sleep = 0;
	} else {
		//printf("Producer wakes up!\n");
		p_sleep = 0;
	}
}

void add_item(){
	buffer[count] = 1;
	count++;
}

void produce_item(){
	add_item();
	if(c_sleep == 1){
		wake_me_up();
	}
	if(show == 1){
		printf("%d\n", count);
		printf("Prod - %d, cons - %d\n\n", p_sleep, c_sleep);
		show = 0;
	}
	//print_buffer();
}

void remove_item(){
	buffer[count-1] = 0;
	count--;
}

void consume_item(){
	remove_item();
	if(p_sleep == 1){
		wake_me_up();
	}
	//print_buffer();
}

void *producer(void* argv){
	while(1){
		flag = 0;
		if(p_sleep == 1){
			//sleep(3);
			continue;
		}
		if(count == BUFFER_SIZE){
			sleep_me_baby();
			continue;
		}
		produce_item();
		sleep(1);
	}
}

void *consumer(void* argv){
	while(1){
		flag = 1;
		if(c_sleep == 1){
			//sleep(3);
			continue;
		}
		if(count == 0){
			sleep_me_baby();
			continue;
		}
		consume_item();
		sleep(1);
	}
}

int main(){
	init();
	for(int i = 0; i < BUFFER_SIZE; i++){
		buffer[i] = 0;
	}

	pthread_t prod, cons;

	int p_rc = pthread_create(&prod, NULL, producer, NULL);
	if(p_rc){
		printf("\n ERROR: return code from producer thread is %d \n", p_rc);
		exit(1);
	}

	int c_rc = pthread_create(&cons, NULL, consumer, NULL);
	if(c_rc){
		printf("\n ERROR: return code from consumer thread is %d \n", c_rc);
		exit(1);
	}
	while(1){
		sleep(10);
		show = 1;
		//print_buffer();
	}
}
