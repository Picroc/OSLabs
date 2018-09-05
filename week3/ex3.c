#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct{
    Node *head;
    int size;
}LinkedList;

void print_list(LinkedList*);
void insert_node(LinkedList*, int);
void remove_node(LinkedList*, int);

int main(){
    LinkedList newList = {NULL, -1};
    insert_node(&newList, 12);
    insert_node(&newList,14);
    insert_node(&newList,2);
    print_list(&newList);
    remove_node(&newList, 1);
    print_list(&newList);
    remove_node(&newList, 0);
    print_list(&newList);
}

void print_list(LinkedList *self){
    if(self->size == -1) {
        printf("No elements in list!\n");
        return;
    }
    Node *current = self->head;
    printf("Printing...\n");

    int counter = 0;
    while(counter < self->size){
        printf("%d ", current->data);
        current = current->next;
        counter++;
    }
    printf("%d ", current->data);
    printf("\n");
}

void insert_node(LinkedList *self, int data){
    Node *element = malloc(sizeof(Node));
    element->data = data;

    if(self->size == -1){
        printf("Setting the first element of list.\n");
        self->head = element;
        self->size++;
        return;
    }


    Node *current = self->head;

    int counter = 0;

    while(counter < self->size){
        current = current->next;
        counter++;
    }
    printf("Setting the new element of list after %d loops.\n", counter);
    current->next = element;
    self->size++;
}

void remove_node(LinkedList *self, int index){
    if(index > self->size){
        printf("There is no such an element!\n");
        return;
    }
    if(index == 0){
        printf("Deleting element 0...\n");
        self->head = self->head->next;
        self->size--;
        return;
    }
    int counter = 0;
    Node *current = self->head;
    while(counter < (index - 1)){
        current = current->next;
        counter++;
    }
    printf("Deleting element %d...\n", index);
    current->next = current->next->next;
    self->size--;
}
