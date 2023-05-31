#include "task.h"
/*PART B*/
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Failed to allocate memory for Queue.\n");
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&(q->lock), NULL);
    pthread_cond_init(&(q->cond), NULL);

    return q;
}

void enqueue(Queue* q, void* data) {
    if (q == NULL) return;
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        perror("Failed to allocate memory for Node.\n");
        return;
    }
    n->data = data;
    n->next = NULL;

    pthread_mutex_lock(&(q->lock));

    if (q->tail == NULL) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    pthread_cond_signal(&(q->cond));
    pthread_mutex_unlock(&(q->lock));
}

void* dequeue(Queue* q) {
    if (q == NULL) return NULL;

    pthread_mutex_lock(&(q->lock));

    while (q->head == NULL) {
        pthread_cond_wait(&(q->cond), &(q->lock));
    }

    node* temp = q->head;
    void* data = temp->data;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    pthread_mutex_unlock(&(q->lock));
    free(temp);

    return data;
}
