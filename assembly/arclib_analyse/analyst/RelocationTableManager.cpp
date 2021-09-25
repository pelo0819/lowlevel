#include "RelocationTableManager.h"

RelocationTableManager::RelocationTableManager(
    uint8_t *head, 
    Elf64_Ehdr *ehdr, 
    Elf64_Shdr *symtab, 
    uint64_t offset)
{
    this->head = head;
    this->p_ehdr = ehdr;
    this->p_sym = symtab;
    this->offset = offset;
}

RelocationTableManager::~RelocationTableManager()
{
}

void RelocationTableManager::AddRelTable(int idx, char *name, Elf64_Rel *rel)
{
    RelocationElement *ele = new RelocationElement(idx, name, rel);
    lstRel.push_back(ele);
}

void RelocationTableManager::CreateRelTable()
{
    int i = 0;
    int j = 0;
    for(i = 0; i < p_ehdr->e_shnum; i++)
    {
        Elf64_Shdr *shdr = (Elf64_Shdr *)(head + p_ehdr->e_shoff + p_ehdr->e_shentsize * i);
        if(shdr->sh_type != SHT_REL && shdr->sh_type != SHT_RELA){ continue; }

        int max = shdr->sh_size / shdr->sh_entsize;

        for(j = 0; j < shdr->sh_size / shdr->sh_entsize; j++)
        {
            Elf64_Rel *rel_table 
                = (Elf64_Rel *)(head + shdr->sh_offset + shdr->sh_entsize * j);
            Elf64_Sym *sym_table 
                = (Elf64_Sym *)(head + p_sym->sh_offset +
                                (p_sym->sh_entsize * ELF64_R_SYM(rel_table->r_info)));
            
            if(!sym_table->st_name){ continue; }
            char *name = (char *)(head + offset + sym_table->st_name);
            AddRelTable(j, name, rel_table);
        }
    }
}

void RelocationTableManager::print_rel_tables(PeloParser *parser)
{
    printf("--- Relocation Table ---\n");
    std::list<RelocationElement *>::iterator it = lstRel.begin();
    while (it != lstRel.end())
    {
        (*it)->print_rel(parser);
        it++;
    }
}
