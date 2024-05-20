#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OPERATIONS 1500000000

int intadd_asm(int a, int b)
{
    int result;
    __asm__("addl %%ebx, %%eax"
            : "=a"(result)
            : "a"(a), "b"(b));
    return result;
}

int intsub_asm(int a, int b)
{
    int result;
    __asm__("subl %%ebx, %%eax"
            : "=a"(result)
            : "a"(a), "b"(b));
    return result;
}

int intmul_asm(int a, int b)
{
    int result;
    __asm__("imull %%ebx, %%eax"
            : "=a"(result)
            : "a"(a), "b"(b));
    return result;
}

int intdiv_asm(int a, int b)
{
    int result;
    if (b == 0)
    {
        b = 1;
    }
    __asm__("movl $0, %%edx;"
            "movl %%eax, %%ebx;"
            "divl %%ecx;"
            : "=a"(result)
            : "a"(a), "c"(b)
            : "ebx", "edx");
    return result;
}

int main()
{
    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    // int a = 100000;
    // int b = 200000;
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
        __asm__(
            "addl %%ebx, %%eax;"
            "subl %%ebx, %%eax;"
            "imull %%ebx, %%eax;"
            "movl $0, %%edx;"
            "test %%ebx, %%ebx;"
            "jz set_one;"
            "jmp end;"
            "set_one:"
            "movl $1, %%ebx;"
            "end:"
            "divl %%ebx;"
            : "=a"(result)
            : "a"(a), "b"(b)
            : "edx");
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // printf("%d\n", result);
    printf("Czas wykonania INT w ASM: %f sekund\n", cpu_time_used);

    return 0;
}