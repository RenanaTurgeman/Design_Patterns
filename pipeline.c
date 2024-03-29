#include "task.h"

size_t N;
size_t seed;

int func1(void *task)
{
    usleep(1000);
    unsigned int num = (rand() % 900001) + 100000; //rand() % (999999 - 100000 + 1) + 999999;
    // printf("AO1: %u\n", num);
    return num;
}

int func2(void *task)
{
    int num = (int)task;
    printf("%d\n", num); // print the number
    printf("%s\n", isPrime(num) ? "true" : "false"); //print if he prime
    num += 11;
    return num;
}

int func3(void *task)
{
    int num = (int)task;
    printf("%d\n", num); // print the number
    printf("%s\n", isPrime(num) ? "true" : "false"); //print if he prime
    num -= 13;
    return num;
}

int func4(void *task)
{
    int num = (int)task;
    printf("%d\n", num); // print the number
    num += 2;
    printf("%d\n", num); // print the number
    return 0;
}

int main(int argc, char *argv[])
{
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
    int run =1;
    while (run)
    {
        sleep(1);
        if (N == 0)
        {
            stop(ao1);
            stop(ao2);
            stop(ao3);
            stop(ao4);
            run=0;
        }
    }

    return run ? 1 :0;
}
