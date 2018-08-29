#include <stdio.h>
#include <string.h>

void swap_f(int* i1, int* i2){
    int foo = *i2;
    *i2 = *i1;
    *i1 = foo;
}

int main ()
{
    int a, b;

    scanf("%d %d", &a, &b);

    printf("Before swap a=%d, b=%d\n", a,b);
    swap_f(&a, &b);
    printf("After swap a=%d, b=%d\n", a,b);


    return 0;
}
