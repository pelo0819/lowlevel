int sample_main();
int pprint(char *s);
int pprintn(unsigned int n);
// char *itoa(int val, char *str);

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

    sample_main();
    return 0;
}
