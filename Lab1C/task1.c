#include <stdio.h>
#include "array.h" 
#include "lab1.h"

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

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    fclose(input);
    return 0;
}
