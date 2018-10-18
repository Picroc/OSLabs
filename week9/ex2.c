#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct Page{
    int p_num;
    int age;
} page_t;

page_t* search_for(page_t **tlb, page_t *page, int n){
    for(int i = 0; i < n; i++){
        if(tlb[i]->p_num == page->p_num){
            return tlb[i];
        }
    }
    return NULL;
}

page_t* get_empty(page_t **tlb, int n){
    for(int i = 0; i < n; i++){
        if(tlb[i]->p_num == -1){
            return tlb[i];
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: ./ex1 <num_of_page_frames>\n");
        return 0;
    }

    int all_hits = 0;
    int hits = 0;

    FILE *ifp = fopen("Lab 09 input2.txt", "r");


    page_t **tlb = malloc(sizeof(page_t) * atoi(argv[1]));


    for(int i = 0, n = atoi(argv[1]); i < n; i++){
        tlb[i] = malloc(sizeof(page_t));
        tlb[i]->p_num = -1;
        tlb[i]->age = 0;
    }


    page_t *buf = malloc(sizeof(page_t));
    while(fscanf(ifp, "%d", &buf->p_num) != EOF){

        all_hits+=1;
        page_t *found = search_for(tlb, buf, atoi(argv[1]));
        if(found != NULL){
            hits += 1;
            //printf("HIT!\n");
            found->age >>= 1;
            found->age |= 1 << 7;
        } else {
            found = get_empty(tlb, atoi(argv[1]));
            if(found != NULL){
                found->p_num = buf->p_num;
                found->age = 1 << 7;
            } else {
                int min = tlb[0]->age;
                page_t *min_page = tlb[0];
                for (int i = 1, n = atoi(argv[1]); i < n; i++) {
                    if (tlb[i]->age < min) {
                        min = tlb[i]->age;
                        min_page = tlb[i];
                    }
                }
                min_page->age = 1 << 7;
                min_page->p_num = buf->p_num;
            }
        }
    }

    printf("%.3f\n", (float) hits/all_hits);
}