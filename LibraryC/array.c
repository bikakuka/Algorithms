#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data *d;
    size_t size;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;
    
    arr->d = (Data*)calloc(size, sizeof(Data));
    if (!arr->d) {
        free(arr);
        return NULL;
    }
    
    arr->size = size;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr){
        if (arr->d) {
            free(arr->d); 
            arr->d = NULL;
        }
        free(arr);
        arr = NULL;                                  
    }
}

// returns specified array element
Data array_get(Array *arr, size_t index)
{
    if (index >= arr->size){
        array_delete(arr);
        exit(1);
    }
    return arr->d[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size){
        array_delete(arr);
        exit(1);
    }
    arr->d[index] = value;
}

// returns array size
size_t array_size( Array *arr)
{
    if (!arr){
        array_delete(arr);
        exit(1);
    }
    return arr->size;
}
