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
// void enqueue(Queue* q, void* data) {
//     printf("start enqueue\n");
//     if (q == NULL) return;
//     node* n = (node*)malloc(sizeof(node));
//     if (n == NULL) {
//         perror("Failed to allocate memory for Node.\n");
//         return;
//     }
//     n->data = data;
//     n->next = NULL;

//     pthread_mutex_lock(&(q->lock));

//     if (q->tail == NULL) {
//         q->head = n;
//         q->tail = n;
//     } else {
//         q->tail->next = n;
//         q->tail = n;
//     }
//     pthread_cond_signal(&(q->cond));
//     pthread_mutex_unlock(&(q->lock));
//     printf("end enqueue\n");
// }

// void* dequeue(Queue* q) {
//     if (q == NULL) return NULL;

//     pthread_mutex_lock(&(q->lock));

//     while (q->head == NULL) {
//         pthread_cond_wait(&(q->cond), &(q->lock));
//     }

//     node* temp = q->head;
//     q->head = q->head->next;
//     void* data = temp->data;
//     if (q->head == NULL) {
//         q->tail = NULL;
//     }

//     free(temp);
//     pthread_mutex_unlock(&(q->lock));

//     return data;
// }
