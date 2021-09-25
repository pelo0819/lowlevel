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
        uint8_t *h = (uint8_t *)ehdr + ehdr->e_phoff + ehdr->e_phentsize * i;
        printf("h(%d): %p\n", i, h);
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

    int copied_size = 0;

    strcpy(file_name, argv[1]);
    printf("[*] attempt to open file. (%s)\n", file_name);

    fd = open(file_name, O_RDONLY);
    if(fd < 0)
    {
        printf("[!!!] cannot open file. (%s)\n", file_name);
        return 1;
    }
    printf("[*] success open file. (%s)\n", file_name);

    fstat(fd, &sb);
    head = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    printf("[*] org elf file: head->%p, size->%ld\n", head, sb.st_size);

    char *copy = "_copy";
    strncat(file_name, copy, sizeof(copy));

    printf("[*] start to make copy (%s)\n", file_name);
    FILE *file = NULL;
    file = fopen(file_name, "wb");
    // fwrite(head, sb.st_size, 1, file);

    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;

    // ELFファイル先頭からプログラムヘッダまでのバイナリデータを書き込む
    ehdr = (Elf64_Ehdr *)head;
    uint8_t *head_phdr = (uint8_t *)ehdr + ehdr->e_phoff;
    uint8_t offset = head_phdr - head;
    printf("[*] offset to phdr from elf file head->%d byte\n", offset);
    fwrite(head, offset, 1, file);
    copied_size += offset;
    head += offset;

    //プログラムヘッダのフラグを777に変更して、書き込む
    int i =0;
    for (i = 0; i < ehdr->e_phnum; i++)
    {
        head_phdr = (uint8_t *)ehdr + ehdr->e_phoff + ehdr->e_phentsize * i;
        phdr = (Elf64_Phdr *)head_phdr;
        // phdr->p_flags = PF_X|PF_W|PF_R;

        offset = ehdr->e_phentsize;

        Elf64_Phdr *phdr_c;
        phdr_c = (Elf64_Phdr *)malloc(sizeof(Elf64_Phdr));
        memcpy(phdr_c, phdr, offset);
        phdr_c->p_flags = PF_X|PF_W|PF_R;

        // printf("h(%d): pnt->%p, offset->%d\n", i, head_phdr, offset);
        fwrite((uint8_t *)phdr_c, offset, 1, file);
        copied_size += offset;
        head += offset;
    }

    // 残りを書き込む
    fwrite(head, sb.st_size - copied_size, 1, file);
    // copied_size += offset;
    // head += offset;

    printf("[*] finish making copy (%s)\n", file_name);

    fclose(file);

    return 0;
}