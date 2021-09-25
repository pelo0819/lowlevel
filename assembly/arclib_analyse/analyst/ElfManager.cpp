#include "ElfManager.h"

ElfManager::ElfManager()
{
    p_parser = new PeloParser;
    p_parser->setup();
    p_ehdr = (Elf64_Ehdr *)head;
}

ElfManager::~ElfManager()
{
    delete p_ehMgr;
    delete p_parser;
    delete p_shMgr;
    delete p_relMgr;
    //delete p_shstrtab;
    //delete p_symtab;
    //delete p_hdr;
    //delete p_strtab;
}

void ElfManager::SetElfHead(uint8_t *h)
{
    head = h;
}


void ElfManager::Analyse()
{
    p_ehdr = (Elf64_Ehdr *)head;

    if(!IsElf(p_ehdr))
    {
        fprintf(stderr, "This is not ELF file.\n");
        exit(1);
    }

    p_shstrtab = (Elf64_Shdr *)(head + p_ehdr->e_shoff + 
                p_ehdr->e_shentsize * p_ehdr->e_shstrndx);
    
    p_ehMgr = new ElfHeaderManager(p_ehdr);
    if(get_flag(flags, PRINT_ELF_HEADER))
    {
        p_ehMgr->print_elf_header(p_parser);
    }

    int i = 0;
    p_shMgr = new SectionHeaderManager(head, p_shstrtab->sh_offset);
    for(i = 0; i < p_ehdr->e_shnum; i++)
    {
        p_shdr = (Elf64_Shdr *)(head + p_ehdr->e_shoff + p_ehdr->e_shentsize * i);

        if(get_flag(flags, PRINT_SECTION_HEADER))
        {
            p_shMgr->print_section_header(p_shdr, p_parser);
        }
        
        // .symtabセクションヘッダを取得
        if(p_shdr->sh_type == SHT_SYMTAB)
        {
            p_symtab = p_shdr;
        }

        // .strtabセクションヘッダを取得
        char *section_name = (char *)(head + p_shstrtab->sh_offset + p_shdr->sh_name);
        if(!strcmp(".strtab", section_name))
        {
            p_strtab = p_shdr;
        }
    }

    for(i = 0; i< p_ehdr->e_phnum; i++)
    {
        p_hdr = (Elf64_Phdr *)(head + p_ehdr->e_phoff + p_ehdr->e_phentsize * i);
        p_phMgr = new ProgramHeaderManager;
        if(get_flag(flags, PRINT_PROGRAM_HEADER))
        {
            p_phMgr->print_program_header(p_hdr, p_parser);
        }
        delete p_phMgr;
    }

    // シンボルテーブルの出力
    if(p_symtab && p_strtab)
    {
        p_symMgr = new SymbolTableManager(p_ehMgr->isExacutable());
        
        if(get_flag(flags, PRINT_SYMBOL_TABLE))
        {
            p_symMgr->print_symbol_tables(p_symtab, head, p_strtab->sh_offset, p_parser, p_shMgr);
        }
        delete p_symMgr;
    }

    p_relMgr = new RelocationTableManager(head, p_ehdr, p_symtab, p_strtab->sh_offset);
    p_relMgr->CreateRelTable();

    if(get_flag(flags, PRINT_RELOCATION_TABLE))
    {
        p_relMgr->print_rel_tables(p_parser);
    }
}

void ElfManager::SetPrintMode(int argc, char **argv)
{
    if(argc > 2)
    {
        char *opt = argv[2];
        char o[1];
        strncpy(o, opt, 1);
        if(!strstr(o, "-"))
        {
            set_on_flag(flags, PRINT_ALL);
            return;
        }

        if(strstr(opt, "e"))
        {
            set_on_flag(flags, PRINT_ELF_HEADER);
        }
        if(strstr(opt, "sh"))
        {
            set_on_flag(flags, PRINT_SECTION_HEADER);    
        }
        if(strstr(opt, "p"))
        {
            set_on_flag(flags, PRINT_PROGRAM_HEADER);
        }
        if(strstr(opt, "sy"))
        {
            set_on_flag(flags, PRINT_SYMBOL_TABLE);
        }
        if(strstr(opt, "r"))
        {
            set_on_flag(flags, PRINT_RELOCATION_TABLE);   
        }
    }
    else
    {
        set_on_flag(flags, PRINT_ALL);
    }
}

void ElfManager::set_on_flag(uint64_t &flags, uint64_t f)
{
    flags |= f; 
}

void ElfManager::set_off_flag(uint64_t &flags, uint64_t f)
{
    flags &= ~f; 
}

bool ElfManager::get_flag(uint64_t &flags, uint64_t f)
{
    return (flags & f);
}

bool ElfManager::IsElf(Elf64_Ehdr *ehdr)
{
    if(ehdr->e_ident[1] == 0x45 &&
       ehdr->e_ident[2] == 0x4c &&
       ehdr->e_ident[3] == 0x46)
    {
        return true;
    }
    return false;
}