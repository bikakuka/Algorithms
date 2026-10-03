#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

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
    Queue *queue = queue_create(NULL);
    if (!queue) return 1;
    check(queue_empty(queue) && queue_get(queue) == 0, "new queue is empty");
    queue_remove(queue);
    queue_insert(queue, 0);
    check(!queue_empty(queue) && queue_get(queue) == 0, "0 in queue dont mean empty");
    queue_remove(queue);
    check(queue_empty(queue), "remove last element");
    queue_delete(queue);

    bool fifo = true;
    for (size_t slots = 2; slots <= 64; slots *= 2) {
        for (size_t head = 0; head < slots; ++head) {
            queue = queue_create(NULL);
            if (!queue) return 1;
            for (size_t i = 0; i < slots; i++) queue_insert(queue, (Data)i);
            for (size_t i = 0; i < head; i++) {
                if (queue_empty(queue) || queue_get(queue) != i) fifo = false;
                queue_remove(queue);
            }
            for (size_t i = slots; i <= slots + head; i++)
                queue_insert(queue, (Data)i);
            for (size_t i = head; i <= slots + head; i++) {
                if (queue_empty(queue) || queue_get(queue) != i) fifo = false;
                queue_remove(queue);
            }
            if (!queue_empty(queue)) fifo = false;
            queue_insert(queue, 123);
            if (queue_empty(queue) || queue_get(queue) != 123) fifo = false;
            queue_remove(queue);
            queue_delete(queue);
        }
    }
    check(fifo, "queue order didnt break after wrap and resize");
    queue = queue_create(myfree);
    if (!queue) return 1;
    bool values = true;
    for (int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(*value));
        if (!value) { queue_delete(queue); return 1; }
        *value = i;
        queue_insert(queue, (Data)value);
    }
    for (int i = 0; i < 40; i++) {
        int *value = (int *)queue_get(queue);
        if (!value || *value != i) values = false;
        queue_remove(queue);
    }
    check(values && freed == 40, "remove gets right value and frees it");
    for (int i = 100; i < 200; i++) {
        int *value = malloc(sizeof(*value));
        if (!value) { queue_delete(queue); return 1; }
        *value = i;
        queue_insert(queue, (Data)value);
    }
    check(freed == 40, "resize didnt free our data");
    queue_delete(queue);
    check(freed == 200, "queue_delete freed everything left");

    queue_insert(NULL, 1);
    queue_remove(NULL);
    queue_delete(NULL);
    check(queue_empty(NULL) && queue_get(NULL) == 0, "NULL operations are safe");
    printf("Results: %d passed, %d failed\n", tp, tf);
    return tf > 0 ? 1 : 0;
}
