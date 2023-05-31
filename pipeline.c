#include "task.h"
pActiveObject ao4, ao3, ao2, ao1;
size_t N;

void func1(void* task) {
    unsigned int num = *((unsigned int*)task);
    printf("AO1: %u\n", num);
    sleep(1); // Sleep for a thousandth of a second
}

void func2(void* task) {
    printf("start func2 \n");
    unsigned int num = *((unsigned int*)task);
    printf("AO2: %u is %s\n", num, isPrime(num) ? "prime" : "not prime");
    num += 11;
    enqueue(getQueue(ao3), &num); // Assuming ao3 is the next active object
}

void func3(void* task) {
    unsigned int num = *((unsigned int*)task);
    printf("AO3: %u is %s\n", num, isPrime(num) ? "prime" : "not prime");
    num -= 13;
    enqueue(getQueue(ao4), &num); // Assuming ao4 is the next active object
}

void func4(void* task) {
    unsigned int num = *((unsigned int*)task);
    printf("AO4: %u\n", num);
    num += 2;
    printf("AO4: New number is %u\n", num);
}

int main(int argc, char *argv[]) {
    unsigned int seed;
    if (argc < 2) {
        printf("You must provide the number of tasks.\n");
        return -1;
    }

    N = atoi(argv[1]);
    seed = (argc == 3) ? atoi(argv[2]) : time(NULL);

    srand(seed);

    
    pActiveObject ao4 = CreateActiveObject(func4, NULL);
    pActiveObject ao3 = CreateActiveObject(func3, ao4);
    pActiveObject ao2 = CreateActiveObject(func2, ao3);
    pActiveObject ao1 = CreateActiveObject(func1, ao2);


    for(unsigned int i = 0; i < N; ++i) {
        unsigned int *task = (unsigned int*)malloc(sizeof(unsigned int));
        *task = rand() % 1000000;
        enqueue(getQueue(ao1), task);
    }

    sleep(1); // allow for processing, you might want to adjust this sleep duration 

    // Stopping all AOs
    stop(ao1);
    printf("after stop ao1\n");
    stop(ao2);
    printf("after stop ao2\n");
    stop(ao3);
    stop(ao4);

    return 0;
}
