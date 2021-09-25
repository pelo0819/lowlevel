#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <elf.h>

#include "PeloParser.h"

class RelocationElement
{
private:
    int idx;
    char name[256];
    Elf64_Rel *ele = NULL;
public:
    RelocationElement(int idx, char *name, Elf64_Rel *e);
    ~RelocationElement();
    void print_rel(PeloParser *parser);
    void print_rel_offset(uint64_t r_offset);
    void print_rel_info(uint64_t r_info, PeloParser *parser);
    void print_rel_addend(uint64_t r_addend);
    void print_blanks();
};

