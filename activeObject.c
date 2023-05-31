#include "task.h"
/*PART C*/

void* active_object_run(void* arg) {
    pActiveObject ao = (pActiveObject)arg;
    while (true) { // We need to define a stopping condition here.
        void* task = dequeue(ao->queue);
        if (task != NULL) {
            ao->func(task);
        }
    }
    return NULL;
}

pActiveObject CreateActiveObject(int (*func)(void *)) {
    pActiveObject ao = (pActiveObject)malloc(sizeof(ActiveObject));
    if (ao == NULL) {
        perror("Failed to allocate memory for ActiveObject.\n");
        return NULL;
    }

    ao->queue = create_queue();
    ao->func = func;
    ao->next = NULL;

    ao->thread = (pthread_t *)malloc(sizeof(pthread_t));
    if (ao->thread == NULL) {
        perror("Failed to allocate memory for ActiveObject thread.\n");
        free(ao);
        return NULL;
    }

    if (pthread_create(ao->thread, NULL, active_object_run, ao) != 0) {
        perror("Failed to create thread for ActiveObject.\n");
        free(ao->thread);
        free(ao->queue);
        free(ao);
        return NULL;
    }

    return ao;
}

Queue* getQueue(pActiveObject ao) {
    return ao->queue;
}

void stop(pActiveObject ao) {
    if (ao != NULL) {
        // We need to implement a way to break out of the while loop in active_object_run here.
        pthread_join(*(ao->thread), NULL);
        free(ao->thread);
        free(ao->queue);
        free(ao);
    }
}
