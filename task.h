#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pthread.h>
#include <stdlib.h>

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
extern size_t N;
typedef void (active_object_func_t)(void);

// Node structure for the queue
typedef struct node {
    void* data;
    struct node* next;
} node_t;

typedef struct {
    node_t* head;
    node_t* tail;
    pthread_mutex_t head_mutex;
    pthread_mutex_t tail_mutex;
    pthread_cond_t cond;
} queue_t;

typedef struct {
    queue_t* queue;
    void (*func)(void*);
    pthread_t thread;
    volatile bool active;
} active_object_t;

bool isPrime(unsigned int num);

//b
queue_t* queue_create() ;
void queue_enqueue(queue_t* q, void* data) ;
void* queue_dequeue(queue_t* q) ;
void queue_destroy(queue_t* q) ;

//c
void* active_object_run(void* arg) ;
// active_object_t* active_object_create(queue_t* queue, void (*func)(void*));
// queue_t* active_object_get_queue(active_object_t* ao) ;
// void active_object_stop(active_object_t* ao) ;

//d
void first_ao_func(void* task) ;
void second_ao_func(void* task) ;
void third_ao_func(void* task) ;
void fourth_ao_func(void* task) ;
int main(int argc, char* argv[]) ;
void* active_object_loop(void* arg) ;
// active_object_t* active_object_create(queue_t* queue, active_object_func_t func) ;
queue_t* active_object_get_queue(active_object_t* ao) ;
void active_object_stop(active_object_t* ao) ;