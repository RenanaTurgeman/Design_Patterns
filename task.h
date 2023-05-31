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


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

extern size_t N;
typedef void (active_object_func_t)(void);

typedef struct node {
    void* data;
    struct node* next;
} node;

typedef struct Queue {
    node* head;
    node* tail;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Queue;

typedef struct _ActiveObject{
    pthread_t *thread;
    Queue* queue;
    int (*func)(void *);
    struct _ActiveObject *next;
} ActiveObject, *pActiveObject;

// PART A
bool isPrime(unsigned int num);

//PART B
Queue* create_queue();
void enqueue(Queue* q, void* data);
void* dequeue(Queue* q);

//PART C
void* active_object_run(void* arg);
pActiveObject CreateActiveObject(int (*func)(void *));
Queue* getQueue(pActiveObject ao);
void stop(pActiveObject ao) ;