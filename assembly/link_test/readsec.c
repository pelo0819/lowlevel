#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "read_pelo.h"

int is_elf(Elf64_Ehdr *ehdr);
void print_elf_header(Elf64_Ehdr *ehdr);
void print_elf_ident(unsigned char *e_ident, int size);
void print_elf_type(uint16_t e_type);
void print_elf_machine(uint16_t e_machine);
void print_elf_version(uint32_t e_version);
void print_elf_entry(uint64_t e_entry);
void print_program_header_offset(uint64_t e_phoff);
void print_section_header_offset(uint64_t e_shoff);
void print_elf_flags(uint32_t e_flags);
void print_elf_header_size(uint16_t e_ehsize);
void print_program_header_entry_size(uint16_t e_phentsize);
void print_program_header_entry_num(uint16_t e_phnum);
void print_section_header_entry_size(uint16_t e_shentsize);
void print_section_header_entry_num(uint16_t e_shnum);
void print_shstrtab_idx(uint16_t e_shstrndx);

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
        shdr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shoff + ehdr->e_shentsize * i);
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

/*
ELFヘッダを出力する
*/
void print_elf_header(Elf64_Ehdr *ehdr)
{
    printf("--- ELF header ---\n");
    print_elf_ident(ehdr->e_ident, sizeof(ehdr->e_ident));
    print_elf_type(ehdr->e_type);
    print_elf_machine(ehdr->e_machine);
    print_elf_version(ehdr->e_version);
    print_elf_entry(ehdr->e_entry);
    print_program_header_offset(ehdr->e_phoff);
    print_section_header_offset(ehdr->e_shoff);
    print_elf_flags(ehdr->e_flags);
    print_elf_header_size(ehdr->e_ehsize);
    print_program_header_entry_size(ehdr->e_phentsize);
    print_program_header_entry_num(ehdr->e_phnum);
    print_section_header_entry_size(ehdr->e_shentsize);
    print_section_header_entry_num(ehdr->e_shnum);
    print_shstrtab_idx(ehdr->e_shstrndx);
    printf("\n");
}

/*
typeを出力する
*/
void print_elf_type(uint16_t e_type)
{
    char *e_type_str = "";
    switch (e_type)
    {
    case 0:
        e_type_str = "No file type";
        break;
    case 1:
        e_type_str = "Relocation file";
        break;
    case 2:
        e_type_str = "Executable file";
        break;
    case 3:
        e_type_str = "Shared object file";
        break;
    default:
        e_type_str = "Unknown";
        break;
    }
    printf("e_type: 0x%x, %s\n",e_type, e_type_str);
}

/*
アーキテクチャを表示する
*/
void print_elf_machine(uint16_t e_machine)
{
    read_file();
    printf("e_machine: 0x%x\n", e_machine);
}

/*
ELFファイルのバージョンを出力する
*/
void print_elf_version(uint32_t e_version)
{
}

/*
実行開始アドレスを出力する
*/
void print_elf_entry(uint64_t e_entry)
{

}

/*
ELFファイル先頭アドレスからprogram header tableの開始アドレスまでのオフセット
*/
void print_program_header_offset(uint64_t e_phoff)
{

}

/*
ELFファイル先頭アドレスからsection header tableの開始アドレスまでのオフセット
*/
void print_section_header_offset(uint64_t e_shoff)
{

}

/*
現在未使用らいし、なんかのフラグ？
*/
void print_elf_flags(uint32_t e_flags)
{

}

/*
ELFヘッダのサイズを出力する
*/
void print_elf_header_size(uint16_t e_ehsize)
{

}

/*
プログラムヘッダのサイズを出力する
*/
void print_program_header_entry_size(uint16_t e_phentsize)
{

}

/*
プログラムヘッダの数を出力する
*/
void print_program_header_entry_num(uint16_t e_phnum)
{

}

/*
セクションヘッダのサイズを出力する
*/
void print_section_header_entry_size(uint16_t e_shentsize)
{

}

/*
セクションヘッダの数を出力する
*/
void print_section_header_entry_num(uint16_t e_shnum)
{

}

/*
shstrtabセクションのセクション番号を出力する
shstrtabセクションには各セクションの名前が格納される
*/
void print_shstrtab_idx(uint16_t e_shstrndx)
{

}

/*
ELFファイルの基本的な情報を出力する
*/
void print_elf_ident(unsigned char *e_ident, int size)
{
    printf("e_ident: \n");

    // マジックナンバ
    printf(" magic       -> [0]:0x%x\n", *e_ident);
    *e_ident++;

    int i = 0;
    for(i = 1; i < 4; i++)
    {
        printf(" magic       -> [%d]:0x%x, %c\n", i, *e_ident, *e_ident);
        *e_ident++;
    }

    char *str = "";
    // ELFファイルが32bitか64bitか
    switch (*e_ident)
    {
    case 1:
        str = "32bit";
        break;
    case 2:
        str = "64bit";
        break;
    default:
        str = "Invalid";
        break;
    }
    printf(" bit         -> [4]:0x%x, %s\n", *e_ident, str);
    *e_ident++;
    
    // エンディアン
    switch (*e_ident)
    {
    case 1:
        str = "ELFDATA2LSB";
        break;
    case 2:
        str = "ELFDATA2MSB";
        break;
    default:
        str = "Invalid";
        break;
    }
    printf(" endian      -> [5]:0x%x, %s\n", *e_ident, str);
    *e_ident++;

    // ファイルのバージョン(currentじゃないとだめらしい)
    str = "Current";
    if(*e_ident == 0)
    {
        str = "Invalid";
    }
    printf(" format ver  -> [6]:0x%x, %s\n", *e_ident, str);
    *e_ident++;

    printf(" abi type    -> [7]:0x%x\n", *e_ident);
    *e_ident++;
    
    printf(" abi ver     -> [8]:0x%x\n", *e_ident);
    
    for(i = 9; i < size; i++)
    {
        *e_ident++;
        printf(" reserve     -> [%d]:0x%x\n", i, *e_ident);
    }
}
