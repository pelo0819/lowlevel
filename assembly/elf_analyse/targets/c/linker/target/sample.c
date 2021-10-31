int pprint(char *s);
int pprintn(unsigned int n);

extern int extvalue;
extern int extbssvalue;
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

// char *str = "aaa\n";
int add(int a, int b);
int sample_main()
{
    int ret = extfunc(6, 9);
    pprintn(ret);
    pprint("\n");
    ret = func();
    pprint("defg\n");
    pprintn(259);
    // pprint("func() = ");pprintn(ret);pprint("\n");
    return ret;
}