#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

static int tp = 0;
static int tf = 0;
static int freed = 0;

static void check(bool expr, const char *msg){
    if (expr) tp++;
    else tf++;
    printf("%s: %s\n", expr ? "PASS" : "FAIL", msg);
}

static void myfree(void *p){
    freed++;
    free(p);
}

int main(void) {
    Vector *vector = vector_create(NULL);
    if (!vector) return 1;
    check(vector_size(vector) == 0, "new vector is empty");
    vector_resize(vector, 3);
    check(vector_size(vector) == 3, "resize to three");
    check(vector_get(vector, 0) == 0 && vector_get(vector, 2) == 0,
          "new cells are zero");
    vector_set(vector, 0, 10);
    vector_set(vector, 1, 20);
    vector_set(vector, 2, 30);
    vector_resize(vector, 100);
    check(vector_size(vector) == 100 && vector_get(vector, 0) == 10 &&
          vector_get(vector, 2) == 30, "data survived resize");
    bool zero = true;
    for (size_t i = 3; i < 100; i++)
        if (vector_get(vector, i) != 0) zero = false;
    check(zero, "all added cells are zero");
    vector_resize(vector, 1);
    vector_resize(vector, 3);
    check(vector_get(vector, 0) == 10 && vector_get(vector, 1) == 0 &&
          vector_get(vector, 2) == 0, "old values didnt come back after resize");
    vector_set(vector, 3, 99);
    check(vector_size(vector) == 3 && vector_get(vector, 3) == 0,
          "out of bounds access");
    vector_resize(vector, 3);
    check(vector_get(vector, 0) == 10, "same size preserves data");
    vector_resize(vector, SIZE_MAX);
    check(vector_size(vector) == 3 && vector_get(vector, 0) == 10,
          "too big size didnt break vector");
    vector_resize(vector, 0);
    check(vector_size(vector) == 0, "resize to zero");
    vector_delete(vector);
    vector = vector_create(myfree);
    if (!vector) return 1;
    int *a = malloc(sizeof(*a));
    int *b = malloc(sizeof(*b));
    int *c = malloc(sizeof(*c));
    if (!a || !b || !c) {
        free(a); free(b); free(c); vector_delete(vector);
        return 1;
    }
    vector_resize(vector, 2);
    if (vector_size(vector) != 2) {
        free(a); free(b); free(c); vector_delete(vector);
        return 1;
    }
    vector_set(vector, 0, (Data)a);
    vector_set(vector, 0, (Data)a);
    check(freed == 0, "same pointer didnt get freed");
    vector_set(vector, 0, (Data)b);
    check(freed == 1, "replacement frees previous object");
    vector_set(vector, 1, (Data)c);
    vector_resize(vector, 1);
    check(freed == 2, "shrink frees removed object");
    vector_delete(vector);
    check(freed == 3, "vector_delete freed last object");

    vector_set(NULL, 0, 1);
    vector_resize(NULL, 10);
    vector_delete(NULL);
    check(vector_size(NULL) == 0 && vector_get(NULL, 0) == 0,
          "NULL operations are safe");
    printf("Results: %d passed, %d failed\n", tp, tf);
    return tf > 0 ? 1 : 0;
}
