extern int extvalue;
extern int extbssvalue;
int extfunc();

static int dummy_value = 3;
static int dummy_bssvalue;
static int value = 21;
static int bssvalue;
char *string;

static void dummy_func(){}

static int func()
{
    value = 5;
    return (extvalue + extbssvalue + value + bssvalue);
}

int main()
{
    extfunc();
    func();
    string = "sample_string2";
    return 0;
}