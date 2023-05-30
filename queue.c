#include "task.h"
/*PART B*/

queue_t* queue_create() {
    queue_t* q = malloc(sizeof(queue_t));
    node_t* dummy = malloc(sizeof(node_t));
    dummy->next = NULL;

    q->head = q->tail = dummy;
    pthread_mutex_init(&q->head_mutex, NULL);
    pthread_mutex_init(&q->tail_mutex, NULL);
    pthread_cond_init(&q->cond, NULL);
    return q;
}

void queue_enqueue(queue_t* q, void* data) {
    node_t* node = malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;

    pthread_mutex_lock(&q->tail_mutex);
    q->tail->next = node;
    q->tail = node;
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->tail_mutex);
}

void* queue_dequeue(queue_t* q) {
    pthread_mutex_lock(&q->head_mutex);
    while (q->head->next == NULL) {
        pthread_cond_wait(&q->cond, &q->head_mutex);
    }

    node_t* old_head = q->head;
    node_t* new_head = old_head->next;
    void* data = new_head->data;
    q->head = new_head;
    pthread_mutex_unlock(&q->head_mutex);

    free(old_head);
    return data;
}

void queue_destroy(queue_t* q) {
    // Empty the queue
    while (q->head != NULL) {
        node_t* tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }

    pthread_mutex_destroy(&q->head_mutex);
    pthread_mutex_destroy(&q->tail_mutex);
    pthread_cond_destroy(&q->cond);
    free(q);
}