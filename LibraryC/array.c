#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data *d;
    size_t size;
    FFree free_func; 
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
    arr->free_func = f;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr){
        if (arr->d) {
            if (arr->free_func){
                for (size_t i = 0; i < arr->size; i++) {
                    if (arr->d[i]) {
                        arr->free_func((void*)arr->d[i]);
                    }
                }
            }
            free(arr->d); 
            arr->d = NULL;
        }
        free(arr);
    }
}

// returns specified array element
Data array_get(Array *arr, size_t index)
{
    if (index >= arr->size){
        exit(1);
    }
    return arr->d[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size){
        exit(1);
    }
    if (arr->free_func && arr->d[index]) {
        arr->free_func((void*)arr->d[index]);
    }
    arr->d[index] = value;
}

// returns array size
size_t array_size( Array *arr)
{
    if (!arr){
        exit(1);
    }
    return arr->size;
}
