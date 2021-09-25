
#include "RelocationElement.h"

RelocationElement::RelocationElement(int idx, char *name, Elf64_Rel *e)
{
    this->idx = idx;
    strcpy(this->name, name);
    this->ele = e;
}

RelocationElement::~RelocationElement()
{
}

void RelocationElement::print_rel(PeloParser *parser)
{
    printf(" [%3d] %s\n", idx, name);
    print_rel_offset(ele->r_offset);
    print_rel_info(ele->r_info, parser);
}

void RelocationElement::print_rel_offset(uint64_t r_offset)
{
    print_blanks();
    printf("offset: 0x%lx\n", r_offset);
}

void RelocationElement::print_rel_info(uint64_t r_info, PeloParser *parser)
{
    // print_blanks();
    // printf("info  : %ld\n", r_info);
    uint64_t high = r_info >> 32;
    uint64_t low = r_info << 32;
    low = low >> 32;
    
    print_blanks();
    printf("symbol idx: %ld\n", high);
    // print_blanks();
    // printf("symbol idx: %ld\n", ELF64_R_SYM(r_info));

    print_blanks();
    printf("type: %s\n", parser->getValue(low, parser->getLstRelocationType()));
    // print_blanks();
    // printf("type: %s\n", parser->getValue(ELF64_R_TYPE(r_info), parser->getLstRelocationType()));
}

void RelocationElement::print_rel_addend(uint64_t r_addend)
{

}

void RelocationElement::print_blanks()
{
    printf("   ");
}

