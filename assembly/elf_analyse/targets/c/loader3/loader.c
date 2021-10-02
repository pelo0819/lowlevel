#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

// #define USE_LOADER_ARGV

extern int say();
extern int add(int a, int b);
extern int jump(void* e, int argc, char** argv);

extern int _start_empty_text;
extern int _end_empty_text;

u_int64_t ent = 0;

typedef void (*func_t)();

void *test();
static Elf64_Shdr *get_shdr(Elf64_Ehdr *ehdr, int num);
static Elf64_Shdr *search_shdr(Elf64_Ehdr *ehdr, char *name);
int IsElf(Elf64_Ehdr *ehdr);
static func_t load_file(u_int8_t *head);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("[!!!] args is not enough.\n");
        return 1;
    }

    int fd;
    struct stat sb;
    u_int8_t *head = NULL;
    func_t f;
    static char file_name[128];

#ifdef USE_LOADER_ARGV
    static char **stackp;
#endif

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
    head = mmap(
        NULL, 
        sb.st_size, 
        PROT_READ, 
        MAP_SHARED, 
        fd, 
        0);

    printf("[*] head=%p, file size=%ld\n", head, sb.st_size);

    f = load_file(head);
    if(f == NULL)
    {
       printf("[!!!] fail to load file.\n");
       return 1; 
    }
    close(fd);

    printf("[*] jump to entry point\n");

    int i = 0;
    char **argv2;
    argv2 = (char **)malloc(sizeof(char *) * (argc - 1));
    for(int i = 0; i < argc - 1; i++)
    {
        int len = strlen(argv[i + 1]) * sizeof(char);
        argv2[i] = (char *)malloc(len);
        strcpy(argv2[i], argv[i + 1]);
    }

    printf("=========================\n");
    int d = jump(f, argc - 1, argv2);
    printf("=========================\n");
    printf("[*] ret = %d\n", d);

    for(int i = 0; i < argc - 1; i++)
    {
        free(argv2[i]);
    }
    free(argv2);

    return 0;
}

static Elf64_Shdr *get_shdr(Elf64_Ehdr *ehdr, int num)
{
    Elf64_Shdr *shdr;
    if(num < 0 || num >= ehdr->e_shnum)
    {
        printf("[!!!] cannot find shdr (%d)\n", num);
        return NULL;
    }
    shdr = (Elf64_Shdr *)((char *)ehdr + ehdr->e_shoff + ehdr->e_shentsize * num);
    return shdr;
}

static Elf64_Shdr *search_shdr(Elf64_Ehdr *ehdr, char *name)
{
    int i;
    Elf64_Shdr *shdr;
    Elf64_Shdr *nhdr;

    nhdr = get_shdr(ehdr, ehdr->e_shstrndx);

    for(i=0;i <ehdr->e_shnum;i++)
    {
        shdr = get_shdr(ehdr, i);
        if(!strcmp((char *)ehdr + nhdr->sh_offset + shdr->sh_name, name))
        {
            printf("[*] found %s\n", name);
            return shdr;
        }
    }
    return NULL;
}

int IsElf(Elf64_Ehdr *ehdr)
{
    if(ehdr->e_ident[1] == 0x45 &&
       ehdr->e_ident[2] == 0x4c &&
       ehdr->e_ident[3] == 0x46)
    {
        return 0;
    }
    return 1;
}

static func_t load_file(u_int8_t *head)
{
    printf("[*] start to load file\n");
    int i;
    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;
    Elf64_Shdr *shdr;
    func_t f;

    ehdr = (Elf64_Ehdr *)head;
    if(IsElf(ehdr))
    {
        printf("[!!!] this is not elf file.\n");
        return NULL;
    }
    /*
    if(ehdr->e_ident[EI_CLASS] != ELF_CLASS)
    {
        printf("[!!!] unknown class. (%d)\n", (int)ehdr->e_ident[EI_CLASS]);
        return NULL;
    }
    if(ehdr->e_ident[EI_DATA] != ELF_DATA)
    {
        printf("[!!!] unknown endian. (%d)\n", (int)ehdr->e_ident[EI_DATA]);
        return NULL;
    }
    */

#ifdef SHOW_LOG
    printf("_start_empty_text = %p\n", &_start_empty_text);
    printf("_end_empty_text = %p\n", &_end_empty_text);
    printf("load head: %p\n", head);
#endif
    for(i = 0 ;i < ehdr->e_phnum; i++)
    {
        printf("[*] Program Header %d:", i);
        phdr = (Elf64_Phdr *)(head + ehdr->e_phoff + ehdr->e_phentsize * i);
        
        switch (phdr->p_type)
        {
        case PT_LOAD:
            printf(" Type:LOAD, s_vaddr = 0x%lx\n", phdr->p_vaddr);
#ifdef SHOW_LOG
            printf("    offset  = 0x%lx\n", phdr->p_offset);
            printf("    flag    = 0x%x\n", phdr->p_flags);
            printf("    filesz  = 0x%lx\n", phdr->p_filesz);
            printf("    (loaded)\n");
#endif
            memcpy((char *)phdr->p_vaddr, head + phdr->p_offset, phdr->p_filesz);
            break;
        default:
            printf(" Type:OTHER\n");
            break;
        }
    }

    shdr = search_shdr(ehdr, ".bss");
    if(shdr)
    {
        printf("[*] clean BBS: 0x%lx, 0x%lx\n", shdr->sh_addr, shdr->sh_size);
        memset((char *)shdr->sh_addr, 0, shdr->sh_size);
    }

    f = (func_t)(ehdr->e_entry);
    printf("[*] Entry point: 0x%lx\n", (u_int64_t)f);

    return f;
}