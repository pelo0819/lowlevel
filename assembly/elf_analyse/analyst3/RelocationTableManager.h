#ifndef __INCLUDE_RELOCATIONTABLEMANAGER_H__
#define __INCLUDE_RELOCATIONTABLEMANAGER_H__

#include <stdio.h>
#include <elf.h>
#include <list>

#include "RelocationElement.h"

class RelocationTableManager
{
private:
    uint8_t *head = NULL;
    Elf64_Ehdr *p_ehdr = NULL;
    Elf64_Shdr *p_sym = NULL;
    uint64_t offset;
    std::list<RelocationElement *> lstRel;
public:
    RelocationTableManager(
        uint8_t *head, 
        Elf64_Ehdr *ehdr, 
        Elf64_Shdr *symtab,
        uint64_t offset
        );
    ~RelocationTableManager();
    void AddRelTable(int idx, char *name, Elf64_Rel *rel);
    void CreateRelTable();
    void print_rel_tables(PeloParser *parser);
};

#endif