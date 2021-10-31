int pprint(char *s);
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

int pprintn(unsigned int n)
{
    char str[20] = {'\0'};
    itoa(n, str);
    pprint(str);
}


int extvalue = 20;
int extbssvalue;

int extfunc(int a, int b)
{
    int ret;
    ret = a + b;
    pprint("extfunc()\n");
    return ret;
}

int add(int a, int b){ return a + b;}