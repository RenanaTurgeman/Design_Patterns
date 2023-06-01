#include "task.h"
/*PART B*/
void* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Failed to allocate memory for Queue.\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    pthread_cond_init(&(q->cond), NULL);
    pthread_mutex_init(&(q->lock), NULL);

    return (void*)q;
}

void free_queue(Queue* queue) {
    if (queue == NULL) {
        return;
    }
    
    pthread_mutex_lock(&queue->lock);
    
    node* current = queue->head;
    while (current != NULL) {
        node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    
    pthread_cond_destroy(&queue->cond);
    pthread_mutex_unlock(&queue->lock);
    pthread_mutex_destroy(&queue->lock);
    
    memset(queue, 0, sizeof(Queue));
    free(queue);
}
