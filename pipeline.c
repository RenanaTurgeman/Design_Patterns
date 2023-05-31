#include "task.h"

size_t N;
size_t seed;

int func1(void *task)
{
    usleep(1000);
    printf("start func1\n");
    unsigned int num = rand() % 1000000;
    printf("AO1: %u\n", num);
    return num;
}

int func2(void *task)
{
    printf("start func2 \n");
    int num = (int)task;
    printf("AO2: %u is %s\n", num, isPrime(num) ? "prime" : "not prime");
    num += 11;
    return num;
}

int func3(void *task)
{
    int num = (int)task;
    printf("AO3: %u is %s\n", num, isPrime(num) ? "prime" : "not prime");
    num -= 13;
    return num;
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
            printf("after stop ao1\n");
            stop(ao2);
            printf("after stop ao2\n");
            stop(ao3);
            stop(ao4);
            run=0;
        }
    }

    printf("the end of the program\n");
    return run ? 1 :0;
}
