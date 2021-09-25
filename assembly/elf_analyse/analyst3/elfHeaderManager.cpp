#include "ElfHeaderManager.h"

ElfHeaderManager::ElfHeaderManager(Elf64_Ehdr *ehdr)
{
    this->ehdr = ehdr;
    if(ehdr->e_type == 2)
    {
        is_exacutable = true;
    }
}

ElfHeaderManager::~ElfHeaderManager()
{
}


/*
typeを出力する
*/
void ElfHeaderManager::print_elf_type(uint16_t e_type)
{
    char e_type_str[24];
    switch (e_type)
    {
    case 0:
        strcpy(e_type_str, "No file type");
        break;
    case 1:
        strcpy(e_type_str, "Relocation file");
        break;
    case 2:
        strcpy(e_type_str, "Executable file");
        break;
    case 3:
        strcpy(e_type_str, "Shared object file");
        break;
    default:
        strcpy(e_type_str, "Unknown");
        break;
    }
    printf("type: 0x%x, %s\n",e_type, e_type_str);
}

/*
アーキテクチャを表示する
*/
void ElfHeaderManager::print_elf_machine(uint16_t e_machine)
{
    PeloParser *parser = new PeloParser;    
    printf("architecture: 0x%x, %s\n", 
           e_machine, 
           parser->getValue(e_machine, parser->getLstMachine()));
    
    delete parser;
}

/*
ELFファイルのバージョンを出力する
*/
void ElfHeaderManager::print_elf_version(uint32_t e_version)
{
    printf("version: 0x%x\n", e_version);
}

/*
プロセスを開始する仮想アドレスを出力する
*/
void ElfHeaderManager::print_elf_entry(uint64_t e_entry)
{
    printf("entty point: 0x%lx\n", e_entry);
}

/*
ELFファイル先頭アドレスからprogram header tableの開始アドレスまでのオフセット
*/
void ElfHeaderManager::print_program_header_offset(uint64_t e_phoff)
{
    printf("offset to program header table from top of file: 0x%lx, %ldbyte\n", e_phoff, e_phoff);
}

/*
ELFファイル先頭アドレスからsection header tableの開始アドレスまでのオフセット
*/
void ElfHeaderManager::print_section_header_offset(uint64_t e_shoff)
{
    printf("offset to section header table from top of file: 0x%lx, %ldbyte\n", e_shoff, e_shoff);
}

/*
現在未使用らいし、なんかのフラグ？
*/
void ElfHeaderManager::print_elf_flags(uint32_t e_flags)
{
    printf("flags: 0x%x\n", e_flags);
}

/*
ELFヘッダのサイズを出力する
*/
void ElfHeaderManager::print_elf_header_size(uint16_t e_ehsize)
{
    printf("size of elf header: 0x%x, %dbyte\n", e_ehsize, e_ehsize);
}

/*
プログラムヘッダのサイズを出力する
*/
void ElfHeaderManager::print_program_header_entry_size(uint16_t e_phentsize)
{
    printf("size of program header: 0x%x, %dbyte\n", e_phentsize, e_phentsize);
}

/*
プログラムヘッダの数を出力する
*/
void ElfHeaderManager::print_program_header_entry_num(uint16_t e_phnum)
{
    printf("num of program header: 0x%x, %d\n", e_phnum, e_phnum);
}

/*
セクションヘッダのサイズを出力する
*/
void ElfHeaderManager::print_section_header_entry_size(uint16_t e_shentsize)
{
    printf("size of section header: 0x%x, %dbyte\n", e_shentsize, e_shentsize);
}

/*
セクションヘッダの数を出力する
*/
void ElfHeaderManager::print_section_header_entry_num(uint16_t e_shnum)
{
    printf("num of section header: 0x%x, %d\n", e_shnum, e_shnum);
}

/*
shstrtabセクションのセクション番号を出力する
shstrtabセクションには各セクションの名前が格納される
*/
void ElfHeaderManager::print_shstrtab_idx(uint16_t e_shstrndx)
{
    printf("index of .shstrtab section: 0x%x, %d\n", e_shstrndx, e_shstrndx);
}

/*
ELFファイルの基本的な情報を出力する
*/
void ElfHeaderManager::print_elf_ident(unsigned char *e_ident, int size, PeloParser *parser)
{
    printf("base info: \n");

    // マジックナンバ
    printf(" magic       -> [0]:0x%x\n", *e_ident);
    *e_ident++;

    int i = 0;
    for(i = 1; i < 4; i++)
    {
        printf(" magic       -> [%d]:0x%x, %c\n", i, *e_ident, *e_ident);
        *e_ident++;
    }

    char str[24];
    // ELFファイルが32bitか64bitか
    switch (*e_ident)
    {
    case 1:
        strcpy(str, "32bit");
        break;
    case 2:
        strcpy(str, "64bit");
        break;
    default:
        strcpy(str, "Invalid");
        break;
    }
    printf(" bit         -> [4]:0x%x, %s\n", *e_ident, str);
    *e_ident++;
    
    // エンディアン
    switch (*e_ident)
    {
    case 1:
        strcpy(str, "ELFDATA2LSB");
        break;
    case 2:
        strcpy(str, "ELFDATA2MSB");
        break;
    default:
        strcpy(str, "Invalid");
        break;
    }
    printf(" endian      -> [5]:0x%x, %s\n", *e_ident, str);
    *e_ident++;

    // ファイルのバージョン(currentじゃないとだめらしい)
    strcpy(str, "Current");

    if(*e_ident == 0)
    {
        strcpy(str, "Invalid");
    }
    printf(" format ver  -> [6]:0x%x, %s\n", *e_ident, str);
    *e_ident++;

    printf(" os/abi      -> [7]:0x%x, %s\n", 
           *e_ident, parser->getValue(*e_ident, 
           parser->getLstAbi()));
    *e_ident++;
    
    printf(" abi ver     -> [8]:0x%x\n", *e_ident);
    
    for(i = 9; i < size; i++)
    {
        *e_ident++;
        printf(" reserve     -> [%d]:0x%x\n", i, *e_ident);
    }
}


/*
ELFヘッダを出力する
*/
void ElfHeaderManager::print_elf_header(PeloParser *parser)
{
    printf("--- ELF header ---\n");
    print_elf_ident(ehdr->e_ident, sizeof(ehdr->e_ident), parser);
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