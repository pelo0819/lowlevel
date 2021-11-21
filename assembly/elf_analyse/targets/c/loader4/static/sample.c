#include <stdio.h>
//#include <string.h>
// #include <stdlib.h>
#include "sample_lib.h"

extern int pprint(char *str);
char *itoa(int val, char *str);
int __stack_chk_fail(void){}

int main(int argc, char *argv[])
{
    // char cat[128];
    // strcpy(cat, "cat love");
    // strncat(cat, " bear\n", 10);
    
    // char str[20] = {'\0'};
    // strncat(str, "\n", 2);
    // itoa(55, str);

    // pprint(cat);
    // pprint(str);

    // char arg[128] = {'\0'};
    // itoa(argc, arg);
    // pprint(arg);
    // pprint("\n");

    // pprint(argv[0]);
    // pprint("\n");

    // pprint(argv[1]);
    // pprint("\n");

    char *str = "hello\n";
    pprint(str);
    
    int a = func(5);
    char str2[20] ={'\0'};
    itoa(a, str2);
    pprint(str2);
    pprint("\n");

    int b = func2(6);
    char str3[20] ={'\0'};
    itoa(b, str3);
    pprint(str3);
    pprint("\n");
    
    
    
    //puts(str);
    // puts("hello");

    return a;
}

char *itoa(int val, char *str)
{
    char    *ret = str;
    int     i;

    if( val<0 )
    {
        *str++ = '-';
        val *= -1;
    }
    while( val )
    {
        for( i=0; str[i]; i++ );
        for( ; i>=0; i-- )
        {
            str[i+1] = str[i];
        }
        *str = "0123456789"[val%10];
        val /= 10;
    }
    return ret;
}

