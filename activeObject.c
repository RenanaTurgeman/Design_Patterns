#include "task.h"
/*PART C*/

void *active_object_run(void *arg)
{
    pActiveObject temp = (pActiveObject)arg;
    void *data;
    int result;
    int done = 0;

    for (int i = 0; i < N; i++)
    {
        if (temp->func != func1){
            pthread_mutex_lock(&temp->queue->lock);
            while (temp->queue->head == NULL) {
                pthread_cond_wait(&temp->queue->cond, &temp->queue->lock);
            }
            data = dequeue(temp->queue);
            pthread_mutex_unlock(&temp->queue->lock);
        }
        
        if (temp->func != NULL)
        {
            result = temp->func(data);
            if (temp->next)
            {
                pthread_mutex_lock(&temp->next->queue->lock);
                enqueue(temp->next->queue, (void *)result);
                pthread_mutex_unlock(&temp->next->queue->lock);
                pthread_cond_signal(&temp->next->queue->cond);
            }
        }
    }
    N = 0;
    return NULL;
}

pActiveObject CreateActiveObject(int (*func)(void *), pActiveObject next)
{
    printf("creatObject\n");
    pActiveObject ao = (pActiveObject)malloc(sizeof(ActiveObject));
    if (ao == NULL)
    {
        perror("Failed to allocate memory for ActiveObject.\n");
        return NULL;
    }

    ao->queue = create_queue();
    ao->func = func;
    ao->next = next;
    ao->thread = NULL;

    ao->thread = (pthread_t *)malloc(sizeof(pthread_t));
    if (ao->thread == NULL)
    {
        perror("Failed to allocate memory for ActiveObject thread.\n");
        free(ao);
        return NULL;
    }

    if (pthread_create(ao->thread, NULL, active_object_run, ao) != 0)
    {
        perror("Failed to create thread for ActiveObject.\n");
        free(ao->thread);
        free(ao->queue);
        free(ao);
        return NULL;
    }

    return ao;
}

Queue *getQueue(pActiveObject ao)
{
    return ao->queue;
}

pActiveObject getNext(pActiveObject ao)
{
    return ao->next;
}

void stop(pActiveObject ao)
{
    if (ao != NULL)
    {
        pthread_cancel(*(ao->thread));
        // free(ao->thread);
        free_queue(ao->queue);
        free(ao);
    }
}

void enqueue(Queue* q, void* data) {
    printf("start enqueue\n");
    if (q == NULL) return;
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        perror("Failed to allocate memory for Node.\n");
        return;
    }
    n->data = data;
    n->next = NULL;

    if (q->tail == NULL) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    printf("end enqueue\n");
}

void* dequeue(Queue* q) {

    node* node = q->head;
    q->head = node->next;
    void *data = node->data;
    free(node);
    return data;
}