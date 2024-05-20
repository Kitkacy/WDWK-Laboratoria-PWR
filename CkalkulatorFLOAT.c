#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OPERATIONS 1500000000

float fadd_asm(float a, float b) {
    float result;
    result = a+b;
    return result;
}

int fsub_asm(int a, int b)
{
    float result;
    result = a-b;
    return result;
}

int fmul_asm(int a, int b)
{
    float result;
    result = a*b;
    return result;
}

int fdiv_asm(int a, int b)
{
    float result;
    if(b == 0.0f) {
        b = 1.0f;
    }
    result = a/b;
    return result;
}

int main()
{
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    //float a = 100000;
    //float b = 200000;
    float result = 0;

    start = clock();

    for (int i = 1; i <= NUM_OPERATIONS; i++)
    {
        /*fadd_asm((a % i), b);
        fsub_asm((a % i), b);
        fmul_asm((a % i), b);
        fdiv_asm((a % i), b);*/

        float a = (100000 % i);
        float b = (200000 % i);
        a = a + b;
        a = a - b;
        a = a * b;
        if (b == 0.0f)
        {
            b = 1.0f;
        }
        result = a / b;
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    //printf("%f\n", result);
    printf("Czas wykonania FLOAT w C: %f sekund\n", cpu_time_used);

    return 0;
}