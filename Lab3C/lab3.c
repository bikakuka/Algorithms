#include <stdio.h>
#include "queue.h"
#include "vector.h"
#include <stdlib.h>
#include <ctype.h>

typedef struct State {
    unsigned char tiles[9];
    size_t parent;
} State;

static const size_t factorial[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

static unsigned char visited[362880] = {0}; // 9!

size_t state_rank(const State *state){
    size_t rank = 0;
    for (size_t i = 0; i < 9; i++) {
        size_t smaller = 0;
        for (size_t j = i + 1; j < 9; j++) {
            if (state->tiles[j] < state->tiles[i]) smaller++;
        }
        rank += smaller * factorial[8 - i]; // сколько перестановок было бы перед нашей
    }
    return rank;
}

int add_neighbors(Vector *states, Queue *queue, size_t parent, unsigned char *visited){
    if (!states || !queue) return 0;
    const State *current = (const State *)vector_get(states, parent);
    if (!current) return 0;
    size_t zero = 0;
    while (zero < 9 && current->tiles[zero] != 0)
        zero++;
    if (zero == 9) return 0;
    size_t neighbors[4];
    size_t count = 0;
    if (zero >= 3) neighbors[count++] = zero - 3;
    if (zero < 6) neighbors[count++] = zero + 3;
    if (zero % 3 > 0) neighbors[count++] = zero - 1;
    if (zero % 3 < 2) neighbors[count++] = zero + 1;
    for (size_t i = 0; i < count; i++) {
        State candidate = *current;
        candidate.tiles[zero] = current->tiles[neighbors[i]];
        candidate.tiles[neighbors[i]] = 0;
        candidate.parent = parent;
        size_t rank = state_rank(&candidate);
        if (visited[rank]) continue;
        State *next = malloc(sizeof(*next));
        if (!next) return 0;
        *next = candidate;
        size_t index = vector_size(states);
        if (index == SIZE_MAX) {
            free(next);
            return 0;
        }
        vector_resize(states, index + 1);
        if (vector_size(states) != index + 1) {
            free(next);
            return 0;
        }
        vector_set(states, index, (Data)next);
        queue_insert(queue, (Data)index);
        visited[rank] = 1;
    }
    return 1;
}

int main(int argc, char **argv){
    if (argc != 2){
        printf("укажите название файла\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror(argv[1]);
        return 1;
    }
    State start = {{0}, SIZE_MAX};
    int seen[9] = {0};
    size_t count = 0;
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (isspace((unsigned char)ch)) continue;
        if (ch < '0' || ch > '8' || count == 9 || seen[ch - '0']) {
            printf("Числа должны быть от 0 до 8 каждое по разу\n");
            fclose(input);
            return 1;
        }
        seen[ch - '0'] = 1;
        start.tiles[count++] = (unsigned char)(ch - '0');
    }
    int read_error = ferror(input);
    fclose(input);
    if (read_error || count != 9) {
        printf("доска не собралась :(\n");
        return 1;
    }
    Vector *states = vector_create(free);
    Queue *queue = queue_create(NULL);
    State *saved = malloc(sizeof(*saved));
    if (!states || !queue || !saved) {
        free(saved);
        queue_delete(queue);
        vector_delete(states);
        printf("память кончилась\n");
        return 1;
    }
    *saved = start;
    vector_resize(states, 1);
    if (vector_size(states) != 1) {
        free(saved);
        queue_delete(queue);
        vector_delete(states);
        printf("память кончилась\n");
        return 1;
    }
    vector_set(states, 0, (Data)saved);
    queue_insert(queue, (Data)0);
    if (queue_empty(queue)) {
        queue_delete(queue);
        vector_delete(states);
        printf("память кончилась\n");
        return 1;
    }
    size_t solution = SIZE_MAX;
    visited[state_rank(&start)] = 1;
    while (!queue_empty(queue)) {
        size_t index = (size_t)queue_get(queue);
        queue_remove(queue);
        const State *current = (const State *)vector_get(states, index);
        int solved = 1;
        for (size_t i = 0; i < 9; i++) {
            if (current->tiles[i] != (i + 1) % 9) {
                solved = 0;
                break;
            }
        }
        if (solved) {
            solution = index;
            break;
        }
        if (!add_neighbors(states, queue, index, visited)) {
            printf("не добавилось новое состояние\n");
            queue_delete(queue);
            vector_delete(states);
            return 1;
        }
    }
    if (solution == SIZE_MAX) {
        printf("нет решения\n");
    } else {
        size_t length = 0;
        for (size_t index = solution; index != SIZE_MAX; ) {
            const State *state = (const State *)vector_get(states, index);
            length++;
            index = state->parent;
        }
        size_t *path = malloc(length * sizeof(*path));
        if (!path) {
            printf("память кончилась\n");
            queue_delete(queue);
            vector_delete(states);
            return 1;
        }
        size_t index = solution;
        for (size_t i = 0; i < length; i++) {
            path[i] = index;
            const State *state = (const State *)vector_get(states, index);
            index = state->parent;
        }
        while (length > 0) {
            index = path[--length];
            const State *state = (const State *)vector_get(states, index);
            for (size_t i = 0; i < 9; i++)
                printf("%u", (unsigned int)state->tiles[i]);
            putchar('\n');
        }
        free(path);
    }
    queue_delete(queue);
    vector_delete(states);
    return 0;
}
