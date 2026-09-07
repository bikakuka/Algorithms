#include <stdio.h>
#include "array.h" 

void task1(Array *arr)
{
    int p, n, z;
    p = z = n = 0;
    for (size_t i = 0; i < array_size(arr); i++){
        if (array_get(arr, i) > 0) p++;
        else if (array_get(arr, i) < 0) n++;
        else z++;
    }
    //printf("positive: %d\nzeros: %d\nnegative: %d\n", p, z, n);
    printf("+: %d\n0: %d\n-: %d\n", p, z, n);
}