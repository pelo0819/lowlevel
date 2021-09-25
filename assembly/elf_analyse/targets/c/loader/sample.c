#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int pprint(char *str);

char *itoa( int val, char *str )
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

int main(int argc, char *argv[])
{
    char cat[100];
    strcpy(cat, "cat love");
    strncat(cat, " bear\n", 10);
    
    char str[20] ={'\0'};
    strncat(str, "\n", 2);
    itoa(55, str);

    pprint(cat);
    pprint(str);

    return 0;
}

