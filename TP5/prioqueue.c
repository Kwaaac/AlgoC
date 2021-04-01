#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "prioqueue.h"
#include "event.h"

#define MAX_QUEUE_SIZE 100

typedef struct _link {
    event *e;
    struct _link *next;
} link;

struct _prioqueue {
    link *first;
    int size;
};

void display_pq(prioqueue *pq){
    if(pq->size <= 0){
        printf("La queue d'event est vide");
    } else{
        link *lk = pq->first;
        while(lk != NULL){
            printf("%d : ", lk->e->etime);
            lk = lk->next;
        }
    }
}

link *init_link_event(event *e, link *next) {
    link *lk = (link *) malloc(sizeof(link));
    lk->e = e;
    lk->next = next;

    return lk;
}

void free_link(link *lk) {
    free(lk);
}

prioqueue *create_pq() {
    prioqueue *q = (prioqueue *) malloc(sizeof(prioqueue));
    q->first = NULL;
    q->size = 0;
    return q;
}

void free_pq(prioqueue *q) {
    free(q);
}

int size_pq(prioqueue *q) {
    return q->size;
}

void insert_pq_rec(link *current_link, link *new_link) {
    if (current_link->next == NULL) {
        current_link->next = new_link;
    } else if (current_link->next->e->etime > new_link->e->etime) {
        new_link->next = current_link->next;
        current_link->next = new_link;
    } else {
        insert_pq_rec(current_link->next, new_link);
    }

}

void insert_pq(prioqueue *q, event *e) {
    assert(q->size < MAX_QUEUE_SIZE);
    link *lk = init_link_event(e, NULL);

    if (q->size == 0) {
        q->first = lk;
    } else {
        if (q->first->e->etime < lk->e->etime) {
            insert_pq_rec(q->first, lk);
        } else {
            lk->next = q->first;
            q->first = lk;
        }
    }

    q->size++;
}

event *remove_min_pq(prioqueue *q) {
    assert(q->size > 0);
    q->size--;
    link *lk = q->first->e;
    event *e = lk->e;

    q->first = q->first->next;

    free_link(lk);

    return e;
}
