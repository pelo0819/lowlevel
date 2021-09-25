#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>


extern int say();
extern int add(int a, int b);
extern int jump();

int main(int argc, char *argv[])
{
    printf("hello\n");
    say();
    return 0;
}