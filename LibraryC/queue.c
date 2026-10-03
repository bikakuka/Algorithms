#include <stdlib.h>
#include "queue.h"
#include "vector.h"

typedef struct Queue {
    Vector *vector;
    size_t head;
    size_t count;
    FFree *freefunc;
} Queue;

Queue *queue_create(FFree f)
{
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->vector = vector_create(NULL); //Очередь владеет данными, а вектор только памятью массива
    if (!queue->vector){
        free(queue);
        return NULL;
    }
    queue->freefunc = f;
    queue->count = 0;
    queue->head = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (!queue) return;
    if (queue->freefunc) {
        size_t slots = vector_size(queue->vector);
        for (size_t i = 0; i < queue->count; i++) {
            size_t index = (queue->head + i) % slots;
            Data value = vector_get(queue->vector, index);
            if (value != 0) queue->freefunc((void *)value);
        }
    }
    vector_delete(queue->vector);
    free(queue);
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    size_t slots = vector_size(queue->vector);
    if (queue->count == slots || slots == 0){
        if (slots == 0) slots++;
        vector_resize(queue->vector, slots * 2);
        if (slots >= vector_size(queue->vector)) return;
        for (size_t i = 0; i < queue->head; i++) {
            Data value = vector_get(queue->vector, i);
            vector_set(queue->vector, slots + i, value);
            vector_set(queue->vector, i, 0);
        }
    }
    vector_set(queue->vector, (queue->head + queue->count) % vector_size(queue->vector), data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (!queue || queue->count == 0) return (Data)0;
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (!queue || queue->count == 0) return;
    Data value = vector_get(queue->vector, queue->head);
    if (queue->freefunc && value != 0) {
        queue->freefunc((void *)value);
    }
    vector_set(queue->vector, queue->head, 0);
    queue->head = (queue->head + 1) % vector_size(queue->vector);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    if (!queue) return true;
    return queue->count == 0;
}
