#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Array;


Array* array_create(size_t size) {
    Array *arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;
    
    arr->data = (int*)calloc(size, sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->size = size;
    return arr;
}

void array_set(Array *arr, size_t i, int value){
    if (i >= arr->size){
        printf("Index out of range\n");
        exit(1);
    }
    arr->data[i] = value;
}

int get_value(Array *arr, size_t i){
    if (i >= arr->size){
        printf("Index out of range\n");
        exit(1);
    }
    return arr->data[i];
}

void array_delete(Array *arr){
    if (arr){
        free(arr->data);
        free(arr);
    }
}

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n);
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
    for (size_t i = 0; i < arr->size; i++){
        if (get_value(arr, i) > 0) p++;
        else if (get_value(arr, i) < 0) n++;
        else z++;
    }
    //printf("positive: %d\nzeros: %d\nnegative: %d\n", p, z, n);
    printf("+: %d\n0: %d\n-: %d\n", p, z, n);
}

void task2(Array *arr)
{
    Array *temp = NULL;
    //printf("values that occur exactly 2 times:\n");
    temp = array_create(1001); // 0,1,2...999,1000
    for (size_t i = 0; i < arr->size; i++){
        int value = get_value(arr, i);
        if (value > 1000 || value < 0){
            printf("some values are greather than 1000 or lower than 0, please input data in [0, 1000] interval ");
            exit(1);
        }
        temp->data[value]++;
    }
    
    for (size_t i = 0; i < temp->size; i++){
        int value = get_value(temp, i);
        if (value == 2) printf("%d ", i);
    }
    // O(arr->size + 1001) => O(n + const) => O(n) 
}

int main(int argc, char **argv){
    if (argc < 2) {
        printf("missing command line argument");
        printf("example of use: .\\Lab1C.exe <PATH TO DATA>");
        return 1;
    }
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}