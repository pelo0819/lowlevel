#include <stdio.h>
#include <stdlib.h>

// extern u_int64_t __start_bindata;
// extern u_int64_t __stop_bindata; 

extern char __start_bindata;
extern char __stop_bindata; 

int main(int argc, char *argv[])
{
    char *p;

    printf("__start_bindata = 0x%08x\n", (int)&__start_bindata);
    printf("__stop_bindata = 0x%08x\n", (int)&__stop_bindata);

    for (p = &__start_bindata; p < &__stop_bindata; p++)
    {
        // printf("i = %d\n", i);
        printf("p=%p\n", p);
        putchar(*p);
        // i++;
    }

    /*
    printf("__start_bindata = 0x%08lx\n", (u_int64_t)&__start_bindata);
    printf("__stop_bindata = 0x%08lx\n", (u_int64_t)&__stop_bindata);

    int cnt = (u_int64_t)&__stop_bindata - (u_int64_t)&__start_bindata;
    printf("cnt = %d\n", cnt);

    int i = 0;
    p = &__start_bindata;
    for(i = 0; i < cnt; i++)
    {
        printf("i = %d\n", i);
        printf("%ln\n", p);
        p++;
    }
    */

    /*
    int i = 0;
    for (p = &__start_bindata; p < &__stop_bindata; p++)
    {
        printf("i = %d\n", i);
        putchar(*p);
        i++;
    }
    */
    return 0;
}


