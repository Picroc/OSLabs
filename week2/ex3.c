#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_tri(int size);

int main(int argc, char *argv[]) {
    int n;

    sscanf(argv[1], "%d", &n);

    printf("%d\n", n);

    print_tri(n);

    return 0;
}

void fill_with_spaces(char* str, int size) {
    for (int i = 0; i < size; i++) {
        str[i] = (char)32;
    }
}

void print_tri(int size) {
    int row_size = (int)(2*size) - 1;

    char row[row_size];
    printf ("%u\n",(unsigned)strlen(row));

    for (int i = 0; i < size; i++) {
        fill_with_spaces(row, row_size);

        int count = 2 * i + 1;
        int init_pos = row_size / 2 - i;
        while (count > 0) {
            row[init_pos] = '*';
            init_pos++;
            count--;
        }

        printf("%s\n", row);
    }
}