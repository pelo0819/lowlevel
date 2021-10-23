int sample_main();
int pprint(char *s);
int pprintn(unsigned int n);
char *itoa(int val, char *str);

int __stack_chk_fail(void){}

int main(int argc, char *argv[])
{
    int i;
    pprint("argc = ");
    pprintn(argc);
    for (i = 0;i < argc; i++)
    {
        pprint(" ");
        pprint(argv[i]);
    }
    pprint("\n");
    i = sample_main();
    pprintn(i);
    pprint("\n");
    return i;
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

int pprintn(unsigned int n)
{
    char str[20] = {'\0'};
    itoa(n, str);
    pprint(str);
}