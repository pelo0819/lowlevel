#include <stdio.h>

int i1 = 0;
int i2[] = {2,2,2};
int *i3;
char s1[] = "this is array";
char *s2 = "this is pointer";

int main()
{
    int i = 55;
    i3 = &i;
    printf(" s1 = 0x%08x\n", (unsigned int)s1);
    printf("&s1 = 0x%08x\n", (unsigned int)&s1);
    printf(" s2 = 0x%08x\n", (unsigned int)s2);
    printf("&s2 = 0x%08x\n", (unsigned int)&s2);
    printf("sizeof(s1) = %d\n", sizeof(s1));
    printf("sizeof(s2) = %d\n", sizeof(s2));
    printf("sizeof(i1) = %d\n", sizeof(i1));
    printf("sizeof(i2) = %d\n", sizeof(i2));
    printf("sizeof(i3) = %d\n", sizeof(i3));
    return 0;
}