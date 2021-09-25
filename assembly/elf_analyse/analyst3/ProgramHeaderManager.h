#ifndef __INCLUDE_PROGRAMHEDADERMANAGER_H__
#define __INCLUDE_PROGRAMHEDADERMANAGER_H__

#include <stdio.h>
#include <elf.h>

#include "PeloParser.h"

class ProgramHeaderManager
{
private:
    /* data */
public:
    ProgramHeaderManager(/* args */);
    ~ProgramHeaderManager();
    void print_program_header(Elf64_Phdr *phdr, PeloParser *parser);
    void print_program_header_type(uint32_t p_type, PeloParser *parser);
    void print_program_header_offset(uint64_t p_offset);
    void print_program_header_virtual_addr(uint64_t p_vaddr, uint64_t p_paddr);
    void print_program_header_file_size(uint64_t p_filesz);
    void print_program_header_memory_size(uint64_t p_memsz);
    void print_program_header_flags(uint32_t p_flags);
    void print_program_header_addralign(uint64_t p_align, uint64_t p_vaddr, uint64_t p_offset);
};

#endif