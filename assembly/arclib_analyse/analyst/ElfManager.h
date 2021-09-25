#ifndef __INCLUDE_ELFMANAGER_H__
#define __INCLUDE_ELFMANAGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

#include "ElfHeaderManager.h"
#include "SectionHeaderManager.h"
#include "ProgramHeaderManager.h"
#include "SymbolTableManager.h"
#include "RelocationTableManager.h"
#include "PeloParser.h"
#include "Constants.h"

#define PRINT_ALL              0xffffffff
#define PRINT_ELF_HEADER       (1 << 1)
#define PRINT_SECTION_HEADER   (1 << 2)
#define PRINT_PROGRAM_HEADER   (1 << 3)
#define PRINT_SYMBOL_TABLE     (1 << 4)
#define PRINT_RELOCATION_TABLE (1 << 5)

class ElfManager
{
private:
    uint64_t flags = 0;
    uint8_t *head = NULL;
    Elf64_Ehdr *p_ehdr = NULL; // pointer to ELF Header
    Elf64_Shdr *p_shdr = NULL; // pointer to Section Header (buffer)
    Elf64_Shdr *p_strtab = NULL;  // pointer to Section .strtab
    Elf64_Shdr *p_shstrtab = NULL; // pointer to Section .shstrtab
    Elf64_Shdr *p_symtab = NULL; // pointer to Section .symtab
    Elf64_Phdr *p_hdr = NULL; // pointer to Program Header (buffer)
    Elf64_Shdr *p_rel = NULL; // pointer to Section .rel(a).xxxx
    PeloParser *p_parser = NULL;
    ElfHeaderManager *p_ehMgr = NULL;
    SectionHeaderManager *p_shMgr = NULL;
    ProgramHeaderManager *p_phMgr = NULL;
    SymbolTableManager *p_symMgr = NULL;
    RelocationTableManager *p_relMgr = NULL;
public:
    ElfManager();
    ~ElfManager();
    void Analyse();
    void SetElfHead(uint8_t *h);
    void SetPrintMode(int argc, char **argv);
    bool IsElf(Elf64_Ehdr *ehdr);
    void set_on_flag(uint64_t &flags, uint64_t f);
    void set_off_flag(uint64_t &flags, uint64_t f);
    bool get_flag(uint64_t &flags, uint64_t f);
};

#endif