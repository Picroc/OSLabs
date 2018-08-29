#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {

    int i = INT_MAX;
    float j = FLT_MAX;
    double k = DBL_MAX;

    printf("Max int: %d;\nMax float: %f;\nMax double: %f;\n", i, j, k);

    return 0;
}