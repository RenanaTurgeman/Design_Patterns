/*PART C*/

#include "task.h"

void* active_object_run(void* arg) {
    active_object_t* ao = (active_object_t*)arg;
    while (!ao->active) {
        void* task = queue_dequeue(ao->queue);
        ao->func(task);
    }
    return NULL;
}

// active_object_t* active_object_create(queue_t* queue, void (*func)(void*)) {
//     active_object_t* ao = malloc(sizeof(active_object_t));
//     ao->queue = queue;
//     ao->func = func;
//     ao->active = true;

//     pthread_create(&ao->thread, NULL, active_object_loop, ao);
//     return ao;
// }

// queue_t* active_object_get_queue(active_object_t* ao) {
//     return ao->queue;
// }

// void active_object_stop(active_object_t* ao) {
//     ao->active = true;
//     pthread_join(ao->thread, NULL);
//     free(ao);
// }