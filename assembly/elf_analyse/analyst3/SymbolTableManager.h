#ifndef __INCLUDE_SYMBOLTABLEMANAGER_H__
#define __INCLUDE_SYMBOLTABLEMANAGER_H__

#include <string>
#include <elf.h>

#include "PeloParser.h"
#include "SectionHeaderManager.h"

class SymbolTableManager
{
private:
    bool is_elf_exacutable = false;
public:
    SymbolTableManager(bool is_exac);
    ~SymbolTableManager();
    void print_symbol_tables(
        Elf64_Shdr *symtab,
        uint8_t *head, 
        uint64_t offset, 
        PeloParser *parser, 
        SectionHeaderManager *shMgr
        );
    void print_symbol_table(
        Elf64_Sym *sym, 
        int idx, 
        uint8_t *name, 
        PeloParser *parser,
        SectionHeaderManager *shMgr
        );
    void print_symbol_table_name(uint32_t st_name);
    void print_symbol_table_value(uint64_t st_value);
    void print_symbol_table_size(uint64_t st_size);
    void print_symbol_table_info(uint8_t st_info, PeloParser *parser);
    void print_symbol_table_other(uint8_t st_other);
    void print_symbol_table_shndx(uint16_t st_shndx, SectionHeaderManager *shMgr);

    void print_blanks();
};

#endif