#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OPERATIONS 1500000000

int intadd_asm(int a, int b)
{
    int result;
    result = a + b;
    return result;
}

int intsub_asm(int a, int b)
{
    int result;
    result = a - b;
    return result;
}

int intmul_asm(int a, int b)
{
    int result;
    result = a * b;
    return result;
}

int intdiv_asm(int a, int b)
{
    int result;
    if (b == 0)
    {
        b = 1;
    }
    result = a / b;
    return result;
}

int main()
{
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    //int a = 100000;
    //int b = 200000;
    int result = 0;


    start = clock();

    for (int i = 1; i <= NUM_OPERATIONS; i++)
    {
        /*intadd_asm((a % i), b);
        intsub_asm((a % i), b);
        intmul_asm((a % i), b);
        intdiv_asm((a % i), b);*/

        

        int a = (100000 % i);
        int b = (200000 % i);
        a = a + b;
        a = a - b;
        a = a * b;
        if (b == 0)
        {
            b = 1;
        }
        result = a / b;
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    //printf("%d\n", result);
    printf("Czas wykonania INT w C: %f sekund\n", cpu_time_used);

    return 0;
}