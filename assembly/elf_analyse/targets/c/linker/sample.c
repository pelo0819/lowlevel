int pprint(char *s);
int pprintn(unsigned int n);

int extvalue;
int extbssvalue;
int extfunc(int a, int b);

static int value = 10;
static int bssvalue;

static int func()
{
    int ret;
    pprint("func()\n");
    pprint("extvalue = ");pprintn(extvalue);pprint("\n");
    pprint("extbssvalue = ");pprintn(extbssvalue);pprint("\n");
    pprint("value = ");pprintn(value);pprint("\n");
    pprint("bssvalue = ");pprintn(bssvalue);pprint("\n");

    return extvalue + extbssvalue + value + bssvalue;
}

int sample_main()
{
    int ret;
    ret = func();
    pprint("sample_main()\n");
    pprint("func() = ");pprintn(ret);pprint("\n");
    return 0;
}