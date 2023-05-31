#include "task.h"
pActiveObject ao4, ao3, ao2, ao1;
size_t N;

int func1(void *task)
{
    usleep(1000);
    printf("start func1\n");
    unsigned int num = rand() % 1000000;
    printf("AO1: %u\n", num);
    return num;
    // enqueue(getQueue(ao2), &num);
}

int func2(void *task)
{
    printf("start func2 \n");
    int num = (int)task;
    printf("AO2: %u is %s\n", num, isPrime(num) ? "prime" : "not prime");
    num += 11;
    return num;
    // enqueue(getQueue(ao3), &num); // Assuming ao3 is the next active object
}

int func3(void *task)
{
    int num = (int)task;
    printf("AO3: %u is %s\n", num, isPrime(num) ? "prime" : "not prime");
    num -= 13;
    return num;
    // enqueue(getQueue(ao4), &num); // Assuming ao4 is the next active object
}

int func4(void *task)
{
    int num = (int)task;
    printf("AO4: %u\n", num);
    num += 2;
    printf("AO4: New number is %u\n", num);
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int seed;
    if (argc < 2)
    {
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

    sleep(1);

    while (true)
    {
        if (N == 0)
        {
            stop(ao1);
            printf("after stop ao1\n");
            stop(ao2);
            printf("after stop ao2\n");
            stop(ao3);
            stop(ao4);
            break;
        }
    }

    return 0;
}
