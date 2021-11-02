#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
struct obj
{
    char *filename;
    char *address;
};

Elf64_Shdr *get_section(Elf64_Ehdr *ehdr, char *name);
int is_symbol_table(Elf64_Sym *symp);
int search_symbol(struct obj objs[], char *name, struct obj *obj);
int relocate_common_symbol(Elf64_Ehdr *ehdr, char *file_name);
int check_ehdr(Elf64_Ehdr *ehdr);
int link_objs(struct obj objs[]);
u_int8_t get_sym_info_high(u_int8_t info);
u_int8_t get_sym_info_low(u_int8_t info);