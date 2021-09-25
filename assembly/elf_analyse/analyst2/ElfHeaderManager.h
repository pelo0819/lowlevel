#ifndef __INCLUDE_ELFHEADERMANAGER_H__
#define __INCLUDE_ELFHEADERMANAGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

#include "PeloParser.h"

class ElfHeaderManager
{
private:
    Elf64_Ehdr *ehdr;
    bool is_exacutable = false;
public:
    ElfHeaderManager(Elf64_Ehdr *ehdr);
    ~ElfHeaderManager();
    bool isExacutable(){ return is_exacutable;}
    void print_elf_header(PeloParser *parser);
    void print_elf_ident(unsigned char *e_ident, int size, PeloParser *parser);
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
};



#endif