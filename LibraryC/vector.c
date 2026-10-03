#include <stdlib.h>
#include "vector.h"

typedef struct Vector {
    Data *data;
    size_t size;
    size_t capacity;
    FFree *freefunc;
} Vector;

Vector *vector_create(FFree f)
{
    Vector *vec = malloc(sizeof(Vector));
    if (!vec) return NULL;
    vec->freefunc = f;
    vec->capacity = 0;
    vec->data = NULL;
    vec->size = 0;
    return vec;
}

void vector_delete(Vector *vector)
{
    if (!vector) return;
    if (vector->freefunc){
        for (size_t i =0; i < vector->size; i++){
            if (vector->data[i] != 0) {
                vector->freefunc((void *)vector->data[i]);
            }
        }
    }
    free(vector->data);
    free(vector);
}

Data vector_get(const Vector *vector, size_t index)
{
    if (!vector) return (Data)0;
    if (index >= vector->size) return (Data)0;
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (!vector) return;
    if (index >= vector->size) return;
    if (vector->freefunc && vector->data[index] != 0 && vector->data[index] != value) {
        vector->freefunc((void *)vector->data[index]);
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    if (!vector) return 0;
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (!vector) return;
    if (SIZE_MAX / sizeof(Data) < size) return;
    if (vector->size == size) return;
    if (vector->size < size){ // доп память выделяется методом геометрического удвоения
        if (size <= vector->capacity){
            for (size_t i = vector->size; i < size; i++){
                vector->data[i] = 0;
            }
            vector->size = size;
        }
        else{
            if (SIZE_MAX / sizeof(Data) < size) return;
            size_t newcap = vector->capacity;
            while (newcap < size){
                if (!newcap) newcap = 1;
                if (SIZE_MAX / sizeof(Data) / 2 < newcap){
                    newcap = size;
                    break;
                }
                newcap *= 2;
            }
            
            Data *new_data = realloc(vector->data, newcap * sizeof(*vector->data));
            if (!new_data) return;
            vector->data = new_data;
            for (size_t i = vector->size; i < size; i++){
                vector->data[i] = 0;
            }
            vector->size = size;
            vector->capacity = newcap; 
        }
    }
    if (vector->size > size){ // не уменьшаю capacity чтобы уменьшить количество вызовов realloc
        // благодаря чему будет реже переноситься по памяти весь вектор
        // ну для realloc не всегда будет место дальше в памяти воооот  
        for (size_t i = size; i < vector->size; i++){
            if (vector->freefunc && vector->data[i] != 0){
                vector->freefunc((void *)vector->data[i]);
            }
            vector->data[i] = 0;
        }
        vector->size = size;
    }
}
