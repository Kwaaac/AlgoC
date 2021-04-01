#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


void display_list(link *lst) {
    link *lk;
    for (lk = lst; lk != NULL; lk = lk->next)
        printf("%d ", lk->c->atime);
    printf("\n");
}

queue *create_q() {
    queue *q = (queue *) malloc(sizeof(queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

link *init_link(customer *c, link *next) {
    link *lk = (link *) malloc(sizeof(link));
    lk->c = c;
    lk->next = next;

    return lk;
}

void enqueue_q(queue *q, customer *c) {
    link *lk = init_link(c, NULL);

    if (q->size == 0) {
        q->first = lk;
        q->last = lk;
    } else {
        lk->next = q->first;
        q->first = lk;
    }

    q->size++;
}

customer *dequeue_q(queue *q) {
    link *lk;
    customer *c;

    c = q->last->c;

    /* loop to get the new last link */
    for (lk = q->first; lk->next != NULL; lk = lk->next) {}

    q->last = lk;
    q->size--;

    return c;
}

void free_q(queue *q) {
    free(q);
}

int size_q(queue *q) {
    return q->size;
}
