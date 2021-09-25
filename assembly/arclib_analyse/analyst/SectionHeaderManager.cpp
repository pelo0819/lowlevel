#include "SectionHeaderManager.h"
#include "PeloParser.h"

SectionHeaderManager::SectionHeaderManager(uint8_t *head, uint64_t offset)
{
    // this->shdr = shdr;
    this->head = head;
    this->offset = offset;
}

SectionHeaderManager::~SectionHeaderManager()
{
}

void SectionHeaderManager::get_section_name(uint32_t idx, char *out)
{
    char *buf = (char *)(head + offset + idx);
    strcpy(out, buf);
}

void SectionHeaderManager::print_section_header(Elf64_Shdr *shdr, PeloParser *parser)
{
    if(shdr->sh_name == 0){ return; }
    char name[128];
    get_section_name(shdr->sh_name, name);
    printf("--- %s ---\n", name);
    print_section_header_name(shdr->sh_name);
    print_section_header_type(shdr->sh_type, parser);
    print_section_header_flags(shdr->sh_flags);
    print_section_header_addr(shdr->sh_addr);
    print_section_header_offset(shdr->sh_offset);
    print_section_header_size(shdr->sh_size);
    print_section_header_link(shdr->sh_link);
    print_section_header_info(shdr->sh_info);
    print_section_header_addralign(shdr->sh_addralign);
    print_section_header_ent_size(shdr->sh_entsize);
}

void SectionHeaderManager::print_section_header_name(uint32_t sh_name)
{
    printf("index: %d\n", sh_name);
}

void SectionHeaderManager::print_section_header_type(uint32_t sh_type, PeloParser *parser)
{
    printf("type: %s\n", parser->getValue(sh_type, parser->getLstSectionType()));
}

void SectionHeaderManager::print_section_header_flags(uint32_t sh_flags)
{
    printf("flags: ");
    if(sh_flags & SHF_WRITE)
    {
        printf("Writable, ");
    }
    if(sh_flags & SHF_ALLOC)
    {
        printf("Alloc (Occupies memory during execution), ");
    }
    if(sh_flags & SHF_EXECINSTR)
    {
        printf("Executable, ");
    }
    if(sh_flags & SHF_MERGE)
    {
        printf("Might be merged, ");
    }
    if(sh_flags & SHF_STRINGS)
    {
        printf("Contains nul-terminated strings, ");
    }
    if(sh_flags & SHF_INFO_LINK)
    {
        printf("`sh_info' contains SHT index, ");
    }
    if(sh_flags & SHF_LINK_ORDER)
    {
        printf("Preserve order after combining, ");
    }
    if(sh_flags & SHF_OS_NONCONFORMING)
    {
        printf("Non-standard OS specific handling required, ");
    }
    if(sh_flags & SHF_GROUP)
    {
        printf("Section is member of a group, ");
    }
    if(sh_flags & SHF_TLS)
    {
        printf("Section hold thread-local data, ");
    }
    if(sh_flags & SHF_COMPRESSED)
    {
        printf("Section with compressed data, ");
    }
    if(sh_flags & SHF_MASKOS)
    {
        printf("OS-specific, ");
    }
    if(sh_flags & SHF_ORDERED)
    {
        printf("Special ordering requirement (Solaris), ");
    }
    if(sh_flags & SHF_EXCLUDE)
    {
        printf("Section is excluded unless referenced or allocated (Solaris), ");
    }
    printf("\n");
}

void SectionHeaderManager::print_section_header_addr(uint64_t sh_addr)
{
    printf("addr: 0x%lx\n", sh_addr);
}

void SectionHeaderManager::print_section_header_offset(uint64_t sh_offset)
{
    printf("offset to section header from top of file: 0x%lx, %ldbyte\n",
           sh_offset, sh_offset);
}

void SectionHeaderManager::print_section_header_size(uint64_t sh_size)
{
    printf("size: %ldbyte\n", sh_size);    
}

void SectionHeaderManager::print_section_header_link(uint32_t sh_link)
{
    printf("link: %d\n", sh_link);
}

void SectionHeaderManager::print_section_header_info(uint32_t sh_info)
{
    printf("info: %d\n", sh_info);
}

void SectionHeaderManager::print_section_header_addralign(uint64_t sh_addralign)
{
    printf("addraign: %ld\n", sh_addralign);
}

void SectionHeaderManager::print_section_header_ent_size(uint64_t sh_entsize)
{
    printf("entry size: %ld\n", sh_entsize);
}