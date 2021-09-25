#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "print_elf_header.h"

int is_elf(Elf64_Ehdr *ehdr);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "args is not enough.\n");
        exit(1);
    }

    int fd;
    int i;
    struct stat sb;
    char *head;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Shdr *shstr;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    head = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

    ehdr = (Elf64_Ehdr *)head;

    if(is_elf(ehdr))
    {
        fprintf(stderr, "This is not ELF file. (%s)\n", argv[1]);
        exit(1);
    }

    shstr = (Elf64_Shdr *)(head + ehdr->e_shoff + 
                ehdr->e_shentsize * ehdr->e_shstrndx);

    print_elf_header(ehdr);

    for(i = 0; i < ehdr->e_shnum; i++)
    {
        shdr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shentsize * i);
        printf("%s\n", (char *)(head + shstr->sh_offset + shdr->sh_name));
    }

    printf("end\n");
    munmap(head, sb.st_size);
    close(fd);

    exit(0);
}

/*
ELFファイルかチェックする
*/
int is_elf(Elf64_Ehdr *ehdr)
{
    if(ehdr->e_ident[1] == 0x45 &&
       ehdr->e_ident[2] == 0x4c &&
       ehdr->e_ident[3] == 0x46)
    {
        return 0;
    }
    return 1;
}

