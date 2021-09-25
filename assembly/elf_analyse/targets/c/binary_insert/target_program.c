#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern u_int64_t __start_bindata;
extern u_int64_t __stop_bindata; 

//extern char __start_bindata;
//extern char __stop_bindata;

int func()
{
    return 5;
}

int main(int argc, char *argv[])
{
    char *p;

    printf("__start_bindata = %p\n", &__start_bindata);
    printf("__stop_bindata  = %p\n", &__stop_bindata);
    
    memcpy(func, &__start_bindata, 15);

    int val = func();
    printf("val = %d\n", val);

    return 0;
}


