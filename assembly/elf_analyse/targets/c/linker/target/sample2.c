int pprint(char *s);
int pprintn(unsigned int n);

int extvalue = 20;
int extbssvalue;

int extfunc(int a, int b)
{
    int ret;
    pprint("extfunc()\n");
    ret = a + b;
    return ret;
}