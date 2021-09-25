#include <stdio.h>

int cnt = 0;

void init1()
{
    cnt++;
    printf("ctors (init1)\n");
}


void (*fp1)(void) __attribute__((section(".ctors"))) = init1;

void __attribute__((constructor)) init()
{
    printf("constructor()\n");
}

void __attribute__((destructor)) fini()
{
    printf("destructor()\n");
}

int main()
{
    printf("main\n");
    printf("cnt = %d\n", cnt);
    return 0;
}