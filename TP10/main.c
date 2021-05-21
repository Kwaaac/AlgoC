#include <stdio.h>
#include "heap.h"

int main() {
    heap *h = create_heap(20);

    insert_heap(h, 5);
    insert_heap(h, 13);
    insert_heap(h, 4);

    insert_heap(h, 14);
    insert_heap(h, 1);
    insert_heap(h, 20);

    extract_min(h);

    printf("\n");
    print_heap_width(h);

    heapsort_with_heap(h->tree, h->size);

    printf("\n");
    print_heap_width(h);

    free_heap(h);
    return 0;
}
