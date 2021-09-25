#include "ProgramHeaderManager.h"

ProgramHeaderManager::ProgramHeaderManager(/* args */)
{
}

ProgramHeaderManager::~ProgramHeaderManager()
{
}

void ProgramHeaderManager::print_program_header(Elf64_Phdr *phdr, PeloParser *parser)
{
    printf("------\n");
    print_program_header_type(phdr->p_type, parser);
    print_program_header_offset(phdr->p_offset);
    print_program_header_virtual_addr(phdr->p_vaddr, phdr->p_paddr);
    print_program_header_file_size(phdr->p_filesz);
    print_program_header_memory_size(phdr->p_memsz);
    print_program_header_flags(phdr->p_flags);
    print_program_header_addralign(phdr->p_align, phdr->p_vaddr, phdr->p_offset);
}

void ProgramHeaderManager::print_program_header_type(uint32_t p_type, PeloParser *parser)
{
    printf("type: %d 0x%x %s\n", p_type, p_type, parser->getValue(p_type, parser->getLstProgramType()) );
}

void ProgramHeaderManager::print_program_header_offset(uint64_t p_offset)
{
    printf("offset to program header from top of file: 0x%lx, %ldbyte\n",
           p_offset, p_offset);
}

void ProgramHeaderManager::print_program_header_virtual_addr(uint64_t p_vaddr, uint64_t p_paddr)
{
    printf("virtual addr: 0x%lx, physical addr: 0x%lx\n", p_vaddr, p_paddr);
}

void ProgramHeaderManager::print_program_header_file_size(uint64_t p_filesz)
{
    printf("file size: 0x%lx, %ldbyte\n", p_filesz, p_filesz);
}

void ProgramHeaderManager::print_program_header_memory_size(uint64_t p_memsz)
{
    printf("memory size: 0x%lx, %ldbyte\n", p_memsz, p_memsz);
}

/*
#define PF_X            (1 << 0)        Segment is executable
#define PF_W            (1 << 1)        Segment is writable
#define PF_R            (1 << 2)        Segment is readable
#define PF_MASKOS       0x0ff00000      OS-specific
#define PF_MASKPROC     0xf0000000      Processor-specific
*/
void ProgramHeaderManager::print_program_header_flags(uint32_t p_flags)
{
    printf("flags: ");
    if(p_flags & PF_X)
    {
        printf("Exectable, ");
    }
    if(p_flags & PF_W)
    {
        printf("Writable, ");
    }
    if(p_flags & PF_R)
    {
        printf("Readable, ");
    }
    if(p_flags & PF_MASKOS)
    {
        printf("OS-specific, ");
    }
    if(p_flags & PF_MASKPROC)
    {
        printf("Processor-specific, ");
    }
    printf("\n");
}

void ProgramHeaderManager::print_program_header_addralign(uint64_t p_align, uint64_t p_vaddr, uint64_t p_offset)
{
    uint64_t surplus1 = 0;
    uint64_t surplus2 = 0; 
    if(p_align > 0)
    {
        surplus1 = p_vaddr % p_align;
        surplus2 = p_offset % p_align;
    }
    printf("align: %ld, vaddr%%align: %ld, offset%%align: %ld\n", p_align, surplus1, surplus2);
}










