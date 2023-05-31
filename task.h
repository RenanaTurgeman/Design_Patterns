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
void* create_queue();
void enqueue(Queue* q, void* data);
void* dequeue(Queue* q);
void free_queue(Queue* queue);

//PART C
void* active_object_run(void* arg);
pActiveObject CreateActiveObject(int (*func)(void *), pActiveObject next);
Queue* getQueue(pActiveObject ao);
pActiveObject getNext(pActiveObject ao);
void stop(pActiveObject ao) ;

//PART D
int func1(void* task);
int func2(void* task) ;
int func3(void* task) ;
int func4(void* task);
int main(int argc, char *argv[]) ;
