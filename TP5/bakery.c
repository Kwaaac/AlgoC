#include <stdio.h>
#include "event.h"
#include "customer.h"
#include "queue.h"
#include "prioqueue.h"

#define N_VENDORS 3
#define VENDOR_TIME 60
#define CLOSING_TIME 420

prioqueue *event_queue;
queue *customer_queue;
customer *vendor[N_VENDORS];
int current_time;

void print_simulation() {
    int i;
    printf("\n%d | ", current_time);

    for (i = 0; i < N_VENDORS; i++) {
        if (vendor[i] == NULL) {
            printf("_");
        } else {
            printf("X");
        }
    }

    printf(" | ");

    for (i = 0; i < size_q(customer_queue); i++) {
        printf("X");
    }
}

void add_customer(customer *c) {
    int i;
    for (i = 0; i < N_VENDORS; i++) {
        if (vendor[i] == NULL) {
            vendor[i] = c;
            return;
        }
    }

    enqueue_q(customer_queue, c);
}

void remove_customer(customer *c) {
    int i;
    event *event;
    customer *c2;

    for (i = 0; i < N_VENDORS; i++) {
        if (vendor[i] == c) {
            vendor[i] = NULL;
            break;
        }
    }

    if (size_q(customer_queue)) {
        c2 = dequeue_q(customer_queue);
        vendor[i] = c2;
        event = create_departure(current_time + 150, c2);
        insert_pq(event_queue, event);
    }

    free_customer(c);
}

void process_arrival(event *e) {
    int time;
    add_customer(e->c);

    time = current_time + 60;
    e->c->atime = current_time + 60;
    event *event = create_arrival(e->c->atime, e->c);
    insert_pq(event_queue, event);
}

void process_departure(event *e) {
    remove_customer(e->c);
}


int main() {
    int i;

    /* Init */
    event_queue = create_pq();
    customer_queue = create_q();
    for (i = 0; i < N_VENDORS; i++) {
        vendor[i] = NULL;
    }
    current_time = 0;

    customer *customer = create_customer(50);

    event *event_arrival = create_arrival(60, customer);
    insert_pq(event_queue, event_arrival);

    while (size_pq(event_queue) && current_time < CLOSING_TIME) {
        event *event = remove_min_pq(event_queue);
        current_time = event->etime;

        printf("Traitement d'un evenement à : %d unité de temps", event->etime);
        switch (event->type) {
            case EVENT_ARRIVAL:
                process_arrival(event);
                break;
            case EVENT_DEPARTURE:
                process_departure(event);
                break;
        }


        print_simulation();
        printf("\n");
        free_event(event);
    }


    free_q(customer_queue);
    free_pq(event_queue);

    return 0;
}