
int pexit();
int main(int, char **);

static void _exit(int status)
{
    pexit();
}

void exit(int status)
{
    _exit(status);
}

// void _start(char *arguments, ...)
// {
//     int argc;
//     char **argv;
//     char **env;

//     argv = &arguments;
//     argc = * (int *)(argv - 1);
//     env = argv + argc + 1;

//     exit( main(argc, argv) );
// }