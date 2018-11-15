#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void copy_arr(int* from, int* to, int n){
    for(int i = 0; i < n; i++){
        to[i] = from[i];
    }
}

void copy_arr2(int** from, int** to, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            to[i][j] = from[i][j];
        }
    }
}

void print_matrix(int **matrix, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void show_stat(int *A, int *E, int m){
    printf("A: ");
    for(int i = 0; i < m; i++){
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("E: ");
    for(int i = 0; i < m; i++){
        printf("%d ", E[i]);
    }
    printf("\n");
}


int main(int argc, char *argv[]){
    if(argc!=2){
        printf("usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        printf("No such file.\n");
        exit(1);
    }

    size_t mem_size = 0;
    char *str_buff = malloc(sizeof(char)*256);
    char *saveptr, *token;
    int m, n;

    int *buf_arr = malloc(sizeof(int)*256);
    int **buf_matrix = malloc(sizeof(int*)*256);
    for(int i = 0; i < 256; i++){
        buf_matrix[i] = malloc(sizeof(int)*256);
    }
    int counter = 0;

    //get E
    fgets(str_buff, 2000, fin);
    token = strtok_r(str_buff, " ", &saveptr);

    while(token!=NULL){
        buf_arr[counter] = atoi(token);
        token = strtok_r(NULL, " ", &saveptr);
        counter++;
    }

    int *E = malloc(sizeof(int)*counter);
    copy_arr(buf_arr, E, counter);

    m = counter;
    counter = 0;

    fgetc(fin);

//    get A
    fgets(str_buff, 2000, fin);
    token = strtok_r(str_buff, " ", &saveptr);

    while(token!=NULL){
        buf_arr[counter] = atoi(token);
        token = strtok_r(NULL, " ", &saveptr);
        counter++;
    }

    int *A = malloc(sizeof(int)*counter);
    copy_arr(buf_arr, A, counter);

    counter = 0;

    fgetc(fin);

//    get C
    int counter_row = 0;

    while (fgets(str_buff, 2000, fin)!=NULL){
        if(strcmp(str_buff, "\n") == 0){
            break;
        }

        counter = 0;

        token = strtok_r(str_buff, " ", &saveptr);
        while (token!=NULL){
            buf_arr[counter] = atoi(token);
            token = strtok_r(NULL, " ", &saveptr);
            counter++;
        }
        copy_arr(buf_arr, buf_matrix[counter_row], counter);
        counter_row++;
    }
    n = counter_row;

    int **C = malloc(sizeof(int*)*n);
    for(int i = 0; i < n; i++){
        C[i] = malloc(sizeof(int)*m);
    }
    copy_arr2(buf_matrix, C, n, m);

    counter = 0;
    counter_row = 0;

//    get R
    counter_row = 0;

    while (fgets(str_buff, 2000, fin)!=NULL){
        if(strcmp(str_buff, "\n") == 0){
            break;
        }

        counter = 0;

        token = strtok_r(str_buff, " ", &saveptr);
        while (token!=NULL){
            buf_arr[counter] = atoi(token);
            token = strtok_r(NULL, " ", &saveptr);
            counter++;
        }
        copy_arr(buf_arr, buf_matrix[counter_row], counter);
        counter_row++;
    }
    n = counter_row;

    int **R = malloc(sizeof(int*)*n);
    for(int i = 0; i < n; i++){
        R[i] = malloc(sizeof(int)*m);
    }
    copy_arr2(buf_matrix, R, n, m);

    counter = 0;
    counter_row = 0;

    printf("Matrix C:\n");
    print_matrix(C, n, m);

    printf("Matrix R:\n");
    print_matrix(R, n, m);

//  END OF THIS DAMN PARSING ////////////////////////////////////////////////////////
//  THE REAL TASK GOES FROM HERE ////////////////////////////////////////////////////


    int running = 0;
    int all_passed = 0;
    int* buff_A = malloc(sizeof(int)*m);

    char deadlocked[256];

    while(running == 0){
        all_passed = 0;
        running = -1;
        sprintf(deadlocked, " ");

        for(int i = 0; i < n; i++){
            int passed = 0;
            int stoped = 0;
            for(int j = 0; j < m; j++){
                if(R[i][j] > A[j]){
                    passed = -1;
                    printf("Process %d hasn't passed.\n", i);
                    break;
                }
                if(R[i][j] != 0 || C[i][j] != 0){
                    stoped = -1;
                }
            }
            if(passed == 0){
                printf("Process %d passed, freeing resources.\n", i);
                for(int j = 0; j < m; j++){
                    A[j] += C[i][j];
                    R[i][j] = 0;
                    C[i][j] = 0;
                }
                if(stoped == -1) {
                    running = 0;
                } else {
                    printf("Process %d stopped.\n", i);
                }
            } else {
                sprintf(deadlocked, "%s %d", deadlocked, i);
                all_passed = -1;
            }
        }

        printf("Deadlocked now: %s\n", deadlocked);
        show_stat(A, E, m);

        if(all_passed == 0){
            printf("No deadlock.\n");
            exit(0);
        }

        sleep(2);
    }
    printf("Ha, deadlock:\n%s\n", deadlocked);
    exit(0);
}

