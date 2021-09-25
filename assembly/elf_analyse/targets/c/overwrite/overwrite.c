#include <stdio.h>
#include <string.h>

int value;
char buffer[100];

void func1()
{
    value += 1;
}

void func2()
{
    value += 2;
}

void func3()
{
    value += 4;
}

int main()
{
    value = 0;
    func1();
    func2();
    func3();

    printf("value=%d\n", value);

    // char *size = (char *)func3 - (char *)func2;
    memcpy(func1, func2, (char *)func3 - (char *)func2);
    // char *size2 = (char *)main - (char *)func3;
    //memcpy(buffer, func3, 100);

    //printf("size =0x%08x\n", size);
    //printf("size2=0x%08x\n", size2);
    //printf("size=%s\n", buffer);

    value = 0;
    printf("value=%d\n", value);
    
    func1();
    func2();
    printf("value=%d\n", value);
    
    ((void(*)())buffer)();
    printf("value=%d\n", value);

    return 0;
}