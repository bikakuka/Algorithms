#include <stdio.h>
#include "array.h"
#include <stdlib.h>

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

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

void task2(Array *arr)
{
    if (!arr) return;
    Array *temp = array_create(1001, NULL);  // 0,1,2...999,1000
    if (!temp) {
        printf("Failed to create temporary array\n");
        return;
    }
    //printf("values that occur exactly 2 times:\n");
    for (size_t i = 0; i < array_size(arr); i++){
        int value = array_get(arr, i);
        if (value > 1000 || value < 0){
            printf("some values are greather than 1000 or lower than 0, please input data in [0, 1000] interval ");
            array_delete(temp);
            array_delete(arr);
            exit(1);
        }
        int val =  array_get(arr, i);
        array_set(temp, val, array_get(temp, val) + 1);
    }
    for (size_t i = 0; i < array_size(temp); i++){
        int value = array_get(temp, i);
        if (value == 2) printf("%d ", i);
    }
    // O(arr->size + 1001) => O(n + const) => O(n) 
}


int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
