#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "event.h"
#include "queue.h"
#include "prioqueue.h"


#define N_VENDORS 3
#define CLOSING_TIME 360
#define ARRIVAL_RATE (1.0/60)
#define MEAN_SERVICE_TIME 150

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

double normal_delay(double mean) {
    return -mean * log(1 - ((double) rand() / RAND_MAX));
}

void add_customer(customer *c) {
    int i;
    event *event;
    for (i = 0; i < N_VENDORS; i++) {
        if (vendor[i] == NULL) {
            vendor[i] = c;
            event = create_departure((int) (current_time + normal_delay(MEAN_SERVICE_TIME)), c);
            insert_pq(event_queue, event);
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
            free_customer(c);
            break;
        }
    }

    if (size_q(customer_queue)) {
        c2 = dequeue_q(customer_queue);
        vendor[i] = c2;
        event = create_departure((int) (current_time + normal_delay(MEAN_SERVICE_TIME)), c2);
        insert_pq(event_queue, event);
    }
}

void process_arrival(event *e) {
    int time;
    customer *customer;
    event *event;
    add_customer(e->c);

    time = (int) (current_time + normal_delay(1.0/ARRIVAL_RATE));
    customer = create_customer(time);

    event = create_arrival(time, customer);
    insert_pq(event_queue, event);
}

void process_departure(event *e) {
    remove_customer(e->c);
}

int main() {
    int i;
    customer *customer;
    event *event_arrival;

    /* Init */
    srand( time( NULL ) );
    event_queue = create_pq();
    customer_queue = create_q();
    for (i = 0; i < N_VENDORS; i++) {
        vendor[i] = NULL;
    }
    current_time = 0;

    customer = create_customer(50);

    event_arrival = create_arrival(60, customer);
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
