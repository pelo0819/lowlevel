#include "loader.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("[!!!] args is not enough.\n");
        return 1;
    }

    int fd;
    struct stat sb;
    u_int8_t *head = NULL;
    func_t f;
    static char file_name[128];

    // void *handle = dlopen("/lib/x86_64-linux-gnu/libc.so.6", RTLD_LAZY);
    
    strcpy(file_name, argv[1]);
    printf("[*] attempt to open file. (%s)\n", file_name);
    
    fd = open(file_name, O_RDWR);
    if(fd < 0)
    {
        printf("[!!!] cannot open file. (%s)\n", file_name);
        return 1;
    }
    printf("[*] success open file. (%s)\n", file_name);

    fstat(fd, &sb);
    head = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    printf("[*] head=%p, file size=%ld\n", head, sb.st_size);

    f = load_file(head);
    if(f == NULL)
    {
       printf("[!!!] fail to load file.\n");
       return 1; 
    }
    close(fd);

    // main()の引数を設定する
    int i = 0;
    char **argv2;
    argv2 = (char **)malloc(sizeof(char *) * (argc - 1));
    for(int i = 0; i < argc - 1; i++)
    {
        int len = strlen(argv[i + 1]) * sizeof(char);
        argv2[i] = (char *)malloc(len);
        strcpy(argv2[i], argv[i + 1]);
    }

    // 通常なら動的リンカが解決するシンボルを前もって解決する
    char *path = "./static/libsample.so";
    dynamic_link(head, path);

    // 実行形式からmain()のシンボルを検索してアドレスを取得する
    char *symbol = "main";
    void *addr;
    addr = search_symbol_in_exec(head, symbol);

    // エントリーポイント(main関数)にジャンプする
    printf("[*] entry point(%s): %p\n", symbol, addr);
    printf("[*] jump to entry point\n");

    printf("\n.........................\n");
    int d = jump(addr, argc - 1, argv2);
    printf(".........................\n\n");
    printf("[*] ret = %d\n", d);

    for(int i = 0; i < argc - 1; i++)
    {
        free(argv2[i]);
    }
    free(argv2);

    return 0;
}

static Elf64_Shdr *get_shdr(Elf64_Ehdr *ehdr, int num)
{
    Elf64_Shdr *shdr;
    if(num < 0 || num >= ehdr->e_shnum)
    {
        printf("[!!!] cannot find shdr (%d)\n", num);
        return NULL;
    }
    shdr = (Elf64_Shdr *)((char *)ehdr + ehdr->e_shoff + ehdr->e_shentsize * num);
    return shdr;
}

static Elf64_Shdr *search_shdr(Elf64_Ehdr *ehdr, char *name)
{
    int i;
    Elf64_Shdr *shdr;
    Elf64_Shdr *nhdr;

    nhdr = get_shdr(ehdr, ehdr->e_shstrndx);

    for(i=0;i <ehdr->e_shnum;i++)
    {
        shdr = get_shdr(ehdr, i);
        if(!strcmp((char *)ehdr + nhdr->sh_offset + shdr->sh_name, name))
        {
            printf("[*] found %s\n", name);
            return shdr;
        }
    }
    return NULL;
}

int IsElf(Elf64_Ehdr *ehdr)
{
    if(ehdr->e_ident[1] == 0x45 &&
       ehdr->e_ident[2] == 0x4c &&
       ehdr->e_ident[3] == 0x46)
    {
        return 0;
    }
    return 1;
}

static func_t load_file(u_int8_t *head)
{
    printf("[*] start to load file\n");
    int i;
    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;
    Elf64_Shdr *shdr;
    func_t f;

    ehdr = (Elf64_Ehdr *)head;
    if(IsElf(ehdr))
    {
        printf("[!!!] this is not elf file.\n");
        return NULL;
    }
    /*
    if(ehdr->e_ident[EI_CLASS] != ELF_CLASS)
    {
        printf("[!!!] unknown class. (%d)\n", (int)ehdr->e_ident[EI_CLASS]);
        return NULL;
    }
    if(ehdr->e_ident[EI_DATA] != ELF_DATA)
    {
        printf("[!!!] unknown endian. (%d)\n", (int)ehdr->e_ident[EI_DATA]);
        return NULL;
    }
    */

#ifdef SHOW_LOG
    printf("_start_empty_text = %p\n", &_start_empty_text);
    printf("_end_empty_text = %p\n", &_end_empty_text);
    printf("load head: %p\n", head);
#endif
    for(i = 0 ;i < ehdr->e_phnum; i++)
    {
#ifdef SHOW_LOG
        printf("[*] Program Header %d:", i);
#endif
        phdr = (Elf64_Phdr *)(head + ehdr->e_phoff + ehdr->e_phentsize * i);
        
        switch (phdr->p_type)
        {
        case PT_LOAD:
        case PT_DYNAMIC:
#ifdef SHOW_LOG
            printf(" Type:LOAD, s_vaddr = 0x%lx\n", phdr->p_vaddr);
            printf("    offset  = 0x%lx\n", phdr->p_offset);
            printf("    flag    = 0x%x\n", phdr->p_flags);
            printf("    filesz  = 0x%lx\n", phdr->p_filesz);
            printf("    (loaded)\n");
#endif
            memcpy((char *)phdr->p_vaddr, head + phdr->p_offset, phdr->p_filesz);
            break;
        /*
        case PT_DYNAMIC:
            printf(" Type:DYNAMIC\n");
            break;
        */
        default:
#ifdef SHOW_LOG     
            printf(" Type:OTHER\n");
#endif
            break;
        }
    }

    shdr = search_shdr(ehdr, ".bss");
    if(shdr)
    {
        printf("[*] clean BBS: 0x%lx, 0x%lx\n", shdr->sh_addr, shdr->sh_size);
        memset((char *)shdr->sh_addr, 0, shdr->sh_size);
    }

    f = (func_t)(ehdr->e_entry);
    // printf("[*] Entry point: 0x%lx\n", (u_int64_t)f);
    return f;
}

/*
shdrで与えたセクションヘッダのセクション名を返す関数
ehdr: shdrが入っているElfヘッダ
      Elfヘッダのe_shstrndxが.shstrtabセクションまでのオフセットを持つためElfヘッダが必要
      .shstrtabに各セクションのセクション名が格納されている
shdr: セクション名を知りたいセクションヘッダ
*/
static char *get_section_name(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    char *head;
    Elf64_Shdr *nhdr;

    head = (char *)ehdr;

    // .shstrtabセクションを取得
    // e_shoff: Elfヘッダの先頭アドレスからセクションヘッダまでのオフセット
    // e_shentsize: 各セクションヘッダのサイズ、sizeof(Elf64_Shdr)と同じでは？面倒だから試さない
    // e_shstrndx: .shstrtabのセクションインデックス
    nhdr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shentsize * ehdr->e_shstrndx);

    // nhdr->sh_offset: Elfファイルの先頭アドレスから.shstrtabセクション先頭までのオフセット
    // shdr->sh_name: .shstrtabセクションのセクション名が格納されるアドレスまでのオフセット
    return ((char *)(head + nhdr->sh_offset + shdr->sh_name));
}

/*
ehdrで与えたElfヘッダからnameで与えたセクション名を検索して、
ヒットしたセクションヘッダを返す関数
ehdr: 検索対象のElfヘッダ
name: 検索するセクション名
*/
Elf64_Shdr *get_section(Elf64_Ehdr *ehdr, char *name)
{
    int i;
    void *head;
    Elf64_Shdr *shdr;

    head = (void *)ehdr;

    for(i = 0;i < ehdr->e_shnum; i++)
    {
        shdr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shentsize * i);
        if(!strcmp(get_section_name(ehdr, shdr), name))
        {
            return shdr;
        }
    }
    return NULL;
}

void *search_symbol_in_exec(u_int8_t *head, char *name)
{
    int i;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Shdr *symtab;
    Elf64_Shdr *strtab;
    Elf64_Sym *symp;

    ehdr = (Elf64_Ehdr *)head;
    symtab = get_section(ehdr, ".symtab");
    strtab = get_section(ehdr, ".strtab");

    // symtabがシンボルテーブルのセクションか確認
    if(symtab->sh_entsize != sizeof(Elf64_Sym))
    {
        printf("[!!!] invalid entry size. (%ld)\n", symtab->sh_entsize);
        return NULL;
    }

    // .symtabセクションの場合、sh_entsizeの大きさの配列状のデータ構造であるので
    // .symtabセクションが終わるまで回して、各シンボル情報に対して解析を行う
    for(i = 0; i < symtab->sh_size; i += symtab->sh_entsize)
    {
        symp = (Elf64_Sym *)(head + symtab->sh_offset + i);
        if(is_symbol_table(symp) != 0)
        {
            continue;
        }

        // シンボル名が格納されているポインタをセット
        char *sym_name = head + strtab->sh_offset + symp->st_name;
        if(!strcmp(name, sym_name))
        {
            shdr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shentsize * symp->st_shndx);
            void *ret;
            ret = (void *)symp->st_value;
            return ret;
        }
    }
    return NULL;
}


/*
引数で与えたsympがシンボルテーブルか確認する
シンボルテーブルなら0を返す
*/
int is_symbol_table(Elf64_Sym *symp)
{
    int falsE = 1;
    // セクション名が格納されるアドレスを示すオフセットが0ならfalse
    if(!symp->st_name)
    {
        return falsE;
    }

    if(symp->st_shndx == SHN_UNDEF || symp->st_shndx == SHN_ABS || symp->st_shndx == SHN_COMMON)
    {
        return falsE;
    }

    if(ELF64_ST_BIND(symp->st_info) != STB_GLOBAL)
    {
        return falsE;
    }

    if(ELF64_ST_TYPE(symp->st_info) != STT_NOTYPE &&
       ELF64_ST_TYPE(symp->st_info) != STT_OBJECT &&
       ELF64_ST_TYPE(symp->st_info) != STT_FUNC)
    {
        return falsE;
    }

    // if(get_sym_info_high(symp->st_info) != STB_GLOBAL)
    // {
    //     return falsE;
    // }

    // if(get_sym_info_low(symp->st_info) != STT_NOTYPE ||
    //    get_sym_info_low(symp->st_info) != STT_OBJECT ||
    //    get_sym_info_low(symp->st_info) != STT_FUNC)
    // {
    //     return falsE;
    // }

    return 0; // true
}

/*
実行形式の動的リンクを行う
head: 実行形式のロード先頭アドレス
path: 実行形式が使用している共有ライブラリのパス
*/
int dynamic_link(void *head, char *path)
{
    void *lib_head = load_common_lib(path);

    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)head;
    Elf64_Shdr *dymsym = get_section(ehdr, ".dynsym");
    if(!dymsym)
    {
        printf("[!!!] .dymsym not exist.\n");
        return 1;
    }

    Elf64_Shdr *dynstr = get_section(ehdr, ".dynstr");
    if(!dynstr)
    {
        printf("[!!!] .dynstr not exist.\n");
    }

    Elf64_Shdr *reltab = get_section(ehdr, ".rela.plt");
    if(!reltab)
    {
        printf("[!!!] .rela.plt not exist\n");
        return 1;
    }

    Elf64_Rela *relp;
    Elf64_Sym *dymp;
    void *sym_addr;
    for(int i = 0; i < reltab->sh_size; i += reltab->sh_entsize)
    {
        relp = (Elf64_Rela *)(head + reltab->sh_offset + i);
        dymp = (Elf64_Sym *)(head + dymsym->sh_offset +
            (dymsym->sh_entsize * ELF64_R_SYM(relp->r_info)));
        
        char *sym_name;
        if(dymp->st_name)
        {
            sym_name = (char *)(head + dynstr->sh_offset + dymp->st_name);
        }
        // printf("offset: %lx\n", relp->r_offset);
        u_int64_t *addp;
        addp = (u_int64_t *)(relp->r_offset);
        // printf("addp: %p, 0x%lx\n", addp, *addp);
        *addp = (u_int64_t)get_symbol_addr_in_common_lib(lib_head, sym_name);
        // printf("2addp: %p, 0x%lx\n", addp, *addp);
    }
    return 0;
}

void *load_common_lib(char *path)
{
    int fd = open(path, O_RDONLY);
    struct stat sb;
    if(fd < 0)
    {
        printf("[!!!] cannot open file (%s)\n", path);
        return NULL;
    }

    fstat(fd, &sb);
    void *lib_head;
    lib_head = mmap(NULL, sb.st_size, PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0);

    // printf("lib_head: %p, size: %d\n", lib_head, sb.st_size);
    return lib_head;
}

void *get_symbol_addr_in_common_lib(void *head, char *name)
{
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)head;
    Elf64_Shdr *dymsym = get_section(ehdr, ".dynsym");
    if(!dymsym)
    {
        printf("[!!!] .dymsym not exist.\n");
        return NULL;
    }

    Elf64_Shdr *dynstr = get_section(ehdr, ".dynstr");
    if(!dynstr)
    {
        printf("[!!!] .dynstr not exist.\n");
        return NULL;
    }

    // TODO: シンボル解決する必要がある共有ライブラリがたぶんある
    /*
    Elf64_Shdr *reltab = get_section(ehdr, ".rela.plt");
    if(!reltab)
    {
        printf("[!!!] .rela.plt not exist\n");
        return NULL;
    }
    */
    Elf64_Rela *relp;
    Elf64_Sym *dymp;
    for(int i = 0; i < dymsym->sh_size / dymsym->sh_entsize; i++)
    {
        dymp = (Elf64_Sym *)(head + dymsym->sh_offset + dymsym->sh_entsize * i);
        if(dymp->st_name)
        {
            char *sym_name = (char *)(head + dynstr->sh_offset + dymp->st_name);
            if(!strcmp(sym_name, name))
            {
                u_int64_t sym_addr = dymp->st_value + (u_int64_t)head;
                printf("[*] found symbol(%s) at 0x%lx\n", sym_name, sym_addr);
                return (void *)sym_addr;
            }
        }
    }
    return NULL;
}

void printp(char *str)
{
#ifdef SHOW_LOG
    printf(str);
#endif
}

