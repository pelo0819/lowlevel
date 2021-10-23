#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include <unistd.h>

#include "linklib.h"

#define Align_4KB 4095
#define Align_16B 15

extern int jump(void* e);

int main(int argc, char *argv[])
{
    int i;
    int n;
    int c;
    int ret;
    FILE *fp;
    char *funcname; // 実行する関数の名前
    char *p;
    struct obj objs[10];
    struct obj obj;
    int (*f)();
    Elf64_Shdr *shdr;
    static char buffer[64 * 1024];

    u_int64_t addr_sample_o;

    memset(buffer, 0, sizeof(buffer));
    p = buffer;
    funcname = argv[1];

    p = (char *)(((u_int64_t)p + Align_4KB) & ~Align_4KB);

    printf("[*] base address is %p\n", buffer);

    for(n = 0, i =2 ;i < argc; n++, i++)
    {
        objs[n].filename = argv[i];
        fp = fopen(objs[n].filename, "rb");
        if(!fp)
        {
            printf("[!!!] cannot open flie %s\n", objs[n].filename);
            return 1;
        }
        objs[n].address = p;
        printf("[*] load to %p (%s)\n", p, objs[n].filename);
        while ((c = fgetc(fp)) != EOF)
        {
            *(p++) = c;
        }
        fclose(fp);

        p = (char *)(((u_int64_t)p + Align_16B) & ~Align_16B);

        check_ehdr((Elf64_Ehdr *)objs[n].address);
        relocate_common_symbol((Elf64_Ehdr *)objs[n].address);

        shdr = get_section((Elf64_Ehdr *)objs[n].address, ".bss");
        if(shdr)
        {
            shdr->sh_offset = p - objs[n].address;
            memset(p, 0, shdr->sh_size);
            p += shdr->sh_size;
        }

        p = (char *)(((u_int64_t)p + Align_16B) & ~Align_16B);
        
        if(n == 0)
        {
            addr_sample_o = (u_int64_t)p;
            printf("addr_sample_o: 0x%lx\n", addr_sample_o);
        }
    }

    objs[n].address = NULL;
    objs[n].filename = NULL;

    link_objs(objs);
    search_symbol(objs, funcname, &obj);
    f = (int (*)())obj.address;
    printf("[*] \n%s is found at %p (%s).\n\n", funcname, f, obj.filename);

    ret = f();
    printf("\n%s return (%d)\n", funcname, ret);

    return 0;
}