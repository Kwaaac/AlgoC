#include "heap.h"
#include <assert.h>
#include <stdio.h>

void print_heap_width(heap *p) {
    int i;
    for (i = 0; i < p->size; i++) {
        printf("%d, ", p->tree[i]);
    }
}

heap *create_heap(int max) {
    heap *new_heap = (heap *) malloc(sizeof(heap));
    assert(new_heap != NULL);

    new_heap->tree = (int *) malloc(max * sizeof(int));
    new_heap->size = 0;
    new_heap->max = max;


    return new_heap;
}

void free_heap(heap *h) {
    free(h->tree);
    free(h);
}

void swap(heap *h, int a, int b) {
    int tmp = h->tree[a];
    h->tree[a] = h->tree[b];
    h->tree[b] = tmp;
}

void swap_tab(int tab[], int a, int b) {
    int tmp = tab[a];
    tab[a] = tab[b];
    tab[b] = tmp;
}

void insert_heap(heap *h, int elt) {
    int i, parent;
    assert(h->size < h->max);
    i = h->size;
    h->size += 1;

    h->tree[i] = elt;

    parent = (i - 1) / 2;
    while (i != 0 && h->tree[i] < h->tree[parent]) {
        swap(h, i, (i - 1) / 2);
        i = parent;
        parent = (i - 1) / 2;
    }

}

int is_heap(heap *h) {
    int i;
    for (i = 0; i < h->size - 1; i++) {
        if (h->tree[i] > h->tree[i + 1]) {
            return 0;
        }
    }

    return 1;
}

int min(heap *h, int a, int b) {
    return h->tree[a] < h->tree[b] ? a : b;
}


int min_child(heap *h, int index) {
    int index_left = index * 2 + 1;
    int index_right = index * 2 + 2;

    if (index_left >= h->size && index_right >= h->size) {
        return -1;
    } else if (index_left >= h->size) {
        return index_right;
    } else if (index_right >= h->size) {
        return index_left;
    } else {
        return min(h, index_left, index_right);
    }
}

int extract_min(heap *h) {
    int swap_index, old_index;
    int min = h->tree[0];
    old_index = 0;
    h->tree[0] = h->tree[h->size - 1];
    h->size -= 1;
    swap_index = min_child(h, old_index);
    while (swap_index != -1) {
        swap(h, swap_index, old_index);

        old_index = swap_index;
        swap_index = min_child(h, old_index);
    }

    return min;
}


void heapify(int tab[], int size, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < size && tab[l] > tab[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < size && tab[r] > tab[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap_tab(tab, i, largest);

        heapify(tab, size, largest);
    }
}

void heapsort(int tab[], int size) {
    int i;
    // Build heap (rearrange array)
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(tab, size, i);

    for (i = size - 1; i > 0; i--) {
        swap_tab(tab, 0, i);

        heapify(tab, i, 0);
    }
}

void heapsort_with_heap(int tab[], int size) {
    int i;
    heap *h = create_heap(size);

    for (i = 0; i < size; i++) {
        insert_heap(h, tab[i]);
    }

    for (i = size - 1; i >= 0; i--) {
        tab[i] = extract_min(h);
    }

    h->tree = tab;
    print_heap_width(h);
}
