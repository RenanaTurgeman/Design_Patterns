
#include "task.h"
void* active_object_loop(void* arg) {
    active_object_t* ao = (active_object_t*) arg;
    while (ao->active) {
        void* task = queue_dequeue(ao->queue);
        ao->func(task);
    }
    return NULL;
}

active_object_t* active_object_create(queue_t* queue, void (*func)(void*)) {
    active_object_t* ao = (active_object_t*) malloc(sizeof(active_object_t));
    ao->active = true;
    ao->queue = queue;
    ao->func = func;
    pthread_create(&ao->thread, NULL, active_object_loop, ao);
    return ao;
}

queue_t* active_object_get_queue(active_object_t* ao) {
    return ao->queue;
}

void active_object_stop(active_object_t* ao) {
    ao->active = false;
    pthread_join(ao->thread, NULL);
    free(ao);
}

void first_ao_func(void* task) {
    unsigned int* num = (unsigned int*)task;
    printf("First AO: Generated number is %d\n", *num);
    usleep(1000); // Sleep for a thousandth of a second
}

void second_ao_func(void* task) {
    unsigned int* num = (unsigned int*)task;
    printf("Second AO: Received number is %d\n", *num);
    printf("Second AO: Number is %s\n", isPrime(*num) ? "prime" : "not prime");
    *num += 11;
}

void third_ao_func(void* task) {
    unsigned int* num = (unsigned int*)task;
    printf("Third AO: Received number is %d\n", *num);
    printf("Third AO: Number is %s\n", isPrime(*num) ? "prime" : "not prime");
    *num -= 13;
}

void fourth_ao_func(void* task) {
    unsigned int* num = (unsigned int*)task;
    printf("Fourth AO: Received number is %d\n", *num);
    *num += 2;
    printf("Fourth AO: Final number is %d\n", *num);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num_tasks> [seed]\n", argv[0]);
        return 1;
    }

    unsigned int num_tasks = atoi(argv[1]);
    unsigned int seed = (argc > 2) ? atoi(argv[2]) : time(NULL);

    srand(seed);

    queue_t* queue1 = queue_create();
    queue_t* queue2 = queue_create();
    queue_t* queue3 = queue_create();

    active_object_t* ao1 = active_object_create(queue1, first_ao_func);
    active_object_t* ao2 = active_object_create(queue2, second_ao_func);
    active_object_t* ao3 = active_object_create(queue3, third_ao_func);
    active_object_t* ao4 = active_object_create(queue3, fourth_ao_func);  // Fourth AO shares the third queue

    for (unsigned int i = 0; i < num_tasks; i++) {
        unsigned int* num = malloc(sizeof(unsigned int));
        *num = rand() % 1000000;  // Generate a six-digit number
        queue_enqueue(active_object_get_queue(ao1), num);
        queue_enqueue(active_object_get_queue(ao2), num);
        queue_enqueue(active_object_get_queue(ao3), num);
    }

    sleep(1);  // Give the AOs time to process all tasks

    active_object_stop(ao1);
    active_object_stop(ao2);
    active_object_stop(ao3);
    active_object_stop(ao4);

    queue_destroy(queue1);
    queue_destroy(queue2);
    queue_destroy(queue3);

    return 0;
}