#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

static int chflg(char *head)
{
    int i;
    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;

    ehdr = (Elf64_Ehdr *)head;

    for (i = 0; i < ehdr->e_phnum; i++)
    {
        phdr = (Elf64_Phdr *)((char *)ehdr + ehdr->e_phoff + ehdr->e_phentsize * i);
        phdr->p_flags = PF_X|PF_W|PF_R;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("[!!!] args is not enough.\n");
        return 1;
    }

    int fd;
    struct stat sb;
    u_int8_t *head;
    static char file_name[128];

    strcpy(file_name, argv[1]);
    printf("[*] attempt to open file. (%s)\n", file_name);

    fd = open(file_name, O_RDWR);
    if(fd < 0)
    {
        printf("[!!!] cannot open file. (%s)\n", file_name);
        return 1;
    }
    printf("[*] success open file. (%s)\n", file_name);

    fstat(fd, &sb);
    head = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(chflg(head) < 0)
    {
        printf("[!!!] fail to change flags\n");
    }

    printf("[*] success to change flags\n");
    close(fd);
    return 0;
}