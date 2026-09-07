#include <stdio.h>
#include <stdlib.h>
#include "array.h" 

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
        if (value == 2) printf("%zu ", i);
    }
    array_delete(temp);
    // O(arr->size + 1001) => O(n + const) => O(n) 
}
