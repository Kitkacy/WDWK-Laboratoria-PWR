#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OPERATIONS 1500000000

float fadd_asm(float a, float b)
{
    float result;
    __asm__("addss %1, %0"
            : "=x"(result)
            : "x"(b), "0"(a));
    return result;
}

float fsub_asm(float a, float b)
{
    float result;
    __asm__("subss %1, %0"
            : "=x"(result)
            : "x"(b), "0"(a));
    return result;
}

float fmul_asm(float a, float b)
{
    float result;
    __asm__("mulss %1, %0"
            : "=x"(result)
            : "x"(b), "0"(a));
    return result;
}

float fdiv_asm(float a, float b)
{
    if (b == 0.0f)
    {
        b = 1.0f;
    }
    float result;
    __asm__("divss %1, %0"
            : "=x"(result)
            : "x"(b), "0"(a));
    return result;
}

int main()
{
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    // float a = 100000;
    // float b = 200000;
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
        __asm__(
            "addss %1, %0\n\t"
            "subss %1, %0\n\t"
            "mulss %1, %0\n\t"
            "test %%ebx, %%ebx\n"
            "jz set_one\n"
            "jmp end\n"
            "set_one:\n"
            "movl $1, %%ebx\n"
            "end:\n"
            "divss %1, %0"
            : "=x"(result)
            : "x"(b), "0"(a)
        );
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    //printf("%f\n", result);
    printf("Czas wykonania FLOAT w ASM: %f sekund\n", cpu_time_used);

    return 0;
}