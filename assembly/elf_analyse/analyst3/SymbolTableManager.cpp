#include <stdio.h>

#include "SymbolTableManager.h"

SymbolTableManager::SymbolTableManager(bool is_exac)
{
    is_elf_exacutable = is_exac;
}

SymbolTableManager::~SymbolTableManager(){}

void SymbolTableManager::print_symbol_tables(
    Elf64_Shdr *symtab, 
    uint8_t *head, 
    uint64_t offset, 
    PeloParser *parser,
    SectionHeaderManager *shMgr)
{
    printf("--- Symbol Table ---\n");
    int i = 0;
    for(i = 0; i < symtab->sh_size / symtab->sh_entsize; i++)
    {
        Elf64_Sym *symbol_table = (Elf64_Sym *)(head + symtab->sh_offset + symtab->sh_entsize * i);
        if(!symbol_table->st_name){ continue;}
        uint8_t *name = (uint8_t *)(head + offset + symbol_table->st_name);
        print_symbol_table(symbol_table, i, name, parser, shMgr);
    }
}


void SymbolTableManager::print_symbol_table(
    Elf64_Sym *sym, 
    int idx, 
    uint8_t *name, 
    PeloParser *parser,
    SectionHeaderManager *shMgr)
{
    printf(" [%3d] %s\n", idx, name);
    print_symbol_table_name(sym->st_name);
    print_symbol_table_value(sym->st_value);
    print_symbol_table_size(sym->st_size);
    print_symbol_table_info(sym->st_info, parser);
    print_symbol_table_other(sym->st_other);
    print_symbol_table_shndx(sym->st_shndx, shMgr);
}

void SymbolTableManager::print_symbol_table_name(uint32_t st_name)
{

}

void SymbolTableManager::print_symbol_table_value(uint64_t st_value)
{
    print_blanks();
    printf("value: 0x%lx\n", st_value);
    /*
    if(is_elf_exacutable)
    {
        printf("value: 0x%lx\n", st_value);
    }
    else
    {

    }
    */
}

void SymbolTableManager::print_symbol_table_size(uint64_t st_size)
{
    print_blanks();
    printf("size: %ld byte\n", st_size);
}

/*
#define STB_LOCAL       0               Local symbol
#define STB_GLOBAL      1               Global symbol 
#define STB_WEAK        2               Weak symbol 
#define STB_NUM         3               Number of defined types.  
#define STB_LOOS        10              Start of OS-specific 
#define STB_GNU_UNIQUE  10              Unique symbol.  
#define STB_HIOS        12              End of OS-specific 
#define STB_LOPROC      13              Start of processor-specific 
#define STB_HIPROC      15              End of processor-specific 
Legal values for ST_TYPE subfield of st_info (symbol type).  
#define STT_NOTYPE      0               Symbol type is unspecified 
#define STT_OBJECT      1               Symbol is a data object 
#define STT_FUNC        2               Symbol is a code object 
#define STT_SECTION     3               Symbol associated with a section 
#define STT_FILE        4               Symbol's name is file name 
#define STT_COMMON      5               Symbol is a common data object 
#define STT_TLS         6               Symbol is thread-local data object
#define STT_NUM         7               Number of defined types.  
#define STT_LOOS        10              Start of OS-specific
#define STT_GNU_IFUNC   10              Symbol is indirect code object
#define STT_HIOS        12              End of OS-specific
#define STT_LOPROC      13              Start of processor-specific
#define STT_HIPROC      15              End of processor-specific
*/
void SymbolTableManager::print_symbol_table_info(uint8_t st_info, PeloParser *parser)
{
    uint8_t high = st_info >> 4;
    uint8_t low = st_info << 4;
    low = low >> 4;
    char *scope = parser->getValue(high, parser->getLstSymbolScope());
    char *type = parser->getValue(low, parser->getLstSymbolType());
    print_blanks();
    printf("high : %d, low : %d\n", high, low);
    print_blanks();
    printf("scope: %s\n", scope);
    print_blanks();
    printf("type : %s\n", type);
}

void SymbolTableManager::print_symbol_table_other(uint8_t st_other)
{
    print_blanks();
    printf("other: %d\n", st_other);
}

/*
#define SHN_UNDEF       0               Undefined section 
#define SHN_LORESERVE   0xff00          Start of reserved indices 
#define SHN_LOPROC      0xff00          Start of processor-specific 
#define SHN_BEFORE      0xff00          Order section before all others
                                           (Solaris).  
#define SHN_AFTER       0xff01          Order section after all others
                                           (Solaris).  
#define SHN_HIPROC      0xff1f          End of processor-specific 
#define SHN_LOOS        0xff20          Start of OS-specific 
#define SHN_HIOS        0xff3f          End of OS-specific 
#define SHN_ABS         0xfff1          Associated symbol is absolute 
#define SHN_COMMON      0xfff2          Associated symbol is common 
#define SHN_XINDEX      0xffff          Index is in extra table.  
#define SHN_HIRESERVE   0xffff          End of reserved indices
*/
void SymbolTableManager::print_symbol_table_shndx(uint16_t st_shndx, SectionHeaderManager *shMgr)
{
    print_blanks();
    printf("seiction name(shndx) %d ", st_shndx);
    // print_blanks();
    char s[128];
    switch (st_shndx)
    {
    case SHN_UNDEF:
        strcpy(s, "UNDEF ( Undefined section )");
        break;
    case SHN_LORESERVE:
        strcpy(s, "LORESERVE ( Start of reserved indices )");
        break;
    /*
    case SHN_LOPROC:
        strcpy(s, "LOPROC ( Start of processor-specific )");
        break;
    case SHN_BEFORE:
        strcpy(s, "BEFORE ( Order section before all others )");
        break;
    */
    case SHN_AFTER:
        strcpy(s, "AFTER ( Order section after all others )");
        break;
    case SHN_HIPROC:
        strcpy(s, "HIPROC ( End of processor-specific )");
        break;
    case SHN_LOOS:
        strcpy(s, "LOOS ( Start of OS-specific )");
        break;
    case SHN_HIOS:
        strcpy(s, "HIOS ( End of OS-specific )");
        break;
    case SHN_ABS:
        strcpy(s, "ABS ( Associated symbol is absolute )");
        break;
    case SHN_COMMON:
        strcpy(s, "COMMON ( Associated symbol is common )");
        break;
    case SHN_XINDEX:
        strcpy(s, "XINDEX ( Index is in extra table )");
        break;
    /*
    case SHN_HIRESERVE:
        strcpy(s, "HIRESERVE ( End of reserved indices )");
        break;
    */
    default:
        char section_name[128];
        //shMgr->get_section_name(st_shndx, section_name);
        std::string name = shMgr->get_section_name(st_shndx);
        //printf("section_name %s\n", section_name);
        strcpy(s, name.c_str());
        break;
    }
    printf("%s\n", s);
}

void SymbolTableManager::print_blanks()
{
    printf("       ");
}
