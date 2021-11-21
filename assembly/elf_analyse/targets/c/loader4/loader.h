#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <dlfcn.h>

extern int jump(void* e, int argc, char** argv);

extern int _start_empty_text;
extern int _end_empty_text;

typedef void (*func_t)();
void *test();
static Elf64_Shdr *get_shdr(Elf64_Ehdr *ehdr, int num);
static Elf64_Shdr *search_shdr(Elf64_Ehdr *ehdr, char *name);
int IsElf(Elf64_Ehdr *ehdr);
static func_t load_file(u_int8_t *head);

static char *get_section_name(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr);
Elf64_Shdr *get_section(Elf64_Ehdr *ehdr, char *name);
void *search_symbol_in_exec(u_int8_t *head, char *name);
int is_symbol_table(Elf64_Sym *symp);
int dynamic_link(void *head, char *path);
void *load_common_lib(char *path);
void *get_symbol_addr_in_common_lib(void *head, char *name);
void printp(char *str);