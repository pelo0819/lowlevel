#ifndef __INCLUDE_SECTIONHEDADERMANAGER_H__
#define __INCLUDE_SECTIONHEDADERMANAGER_H__

#include <stdio.h>
#include <vector>
#include <string>
#include <elf.h>

#include "PeloParser.h"

class SectionIndexName
{
private:
    int idx;
    std::string name;
public:
    SectionIndexName(int i, std::string n){idx = i;name = n;};
    ~SectionIndexName();
    void Setup(int i, std::string n){idx = i;name = n;}
    int getIndex(){return idx;}
    std::string getName(int idx){return name;}

};

class SectionHeaderManager
{
private:
    // Elf64_Shdr *shdr
    uint8_t *head;
    uint64_t offset;
    std::vector<SectionIndexName *> listIdxName;
public:
    SectionHeaderManager(uint8_t *head, uint64_t offset);
    ~SectionHeaderManager();
    void RegistSectionIdxName(int i, char *name);
    void get_section_name(uint32_t idx, char *out);
    std::string get_section_name(int idx);

    void print_section_header(Elf64_Shdr *shdr, PeloParser *parser);
    void print_section_header_name(uint32_t sh_name);
    void print_section_header_type(uint32_t sh_type, PeloParser *parser);
    void print_section_header_flags(uint32_t sh_flags);
    void print_section_header_addr(uint64_t sh_addr);
    void print_section_header_offset(uint64_t sh_offset);
    void print_section_header_size(uint64_t sh_size);
    void print_section_header_link(uint32_t sh_link);
    void print_section_header_info(uint32_t sh_info);
    void print_section_header_addralign(uint64_t addralign);
    void print_section_header_ent_size(uint64_t sh_ent_size);

};

#endif
