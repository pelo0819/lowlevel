#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include <unistd.h>

#include "linklib.h"

#define Align_4KB 4095

int main(int argc, char *argv[])
{
    int i;
    int n;
    int c;
    int ret;
    FILE *fp;
    char *funcname; // 実行する関数の名前
    char *p;
    struct obj objs[10];
    struct obj obj;
    int (*f)();
    Elf64_Shdr *shdr;
    static char buffer[64 * 1024];

    memset(buffer, 0, sizeof(buffer));
    p = buffer;
    funcname = argv[1];

    p = (char *)(((u_int64_t)p + Align_4KB) & ~Align_4KB);

    printf("[*] base address is %p\n", buffer);

    for(n = 0, i =2 ;i < argc; n++, i++)
    {

    }


    return 0;
}