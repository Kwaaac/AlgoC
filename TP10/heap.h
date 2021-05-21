
#ifndef TP10_HEAP_H
#define TP10_HEAP_H
#include <stdlib.h>

typedef struct {
    int *tree;
    int size;
    int max;
} heap;

void print_heap_width(heap *p);

heap *create_heap(int max);

void free_heap(heap *h);

void insert_heap(heap *h, int elt);

int is_heap(heap *h);

int extract_min(heap *h);

void heapsort(int tab[], int size);

void heapsort_with_heap(int tab[], int size);

#endif /*TP10_HEAP_H*/
