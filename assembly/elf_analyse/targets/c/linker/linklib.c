
#include "linklib.h"

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

/*
objsで与えたオブジェクトファイルからnameで与えたシンボルを検索し、objに返す関数
objs: オブジェクトファイルのファイル名と先頭アドレスを持つ構造体
name: 検索したいシンボル名
obj : 検索結果を入れる構造体
*/
int search_symbol(struct obj objs[], char *name, struct obj *obj)
{
    int i;
    int n;
    char *head;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Shdr *symtab;
    Elf64_Shdr *strtab;
    Elf64_Sym *symp;

    // filenameがNULLになるまで回す
    for(n = 0; objs[n].filename; n++)
    {
        // オブジェクトファイルの先頭アドレスをElfヘッダにキャスト
        ehdr = (Elf64_Ehdr *)objs[n].address;
        symtab = get_section(ehdr, ".symtab");
        strtab = get_section(ehdr, ".strtab");
        head = (char *)ehdr;

        // symtabがシンボルテーブルのセクションか確認
        if(symtab->sh_entsize != sizeof(Elf64_Sym))
        {
            printf("[!!!] invalid entry size. (%ld)\n", symtab->sh_entsize);
            return 1;
        }

        // .symtabセクションの場合、sh_entsizeの大きさの配列状のデータ構造であるので
        // .symtabセクションが終わるまで回して、各シンボル情報に対して解析を行う
        for(i = 0; i < symtab->sh_size; i += symtab->sh_entsize)
        {
            symp = (Elf64_Sym *)(head + symtab->sh_offset + i);
            if(!is_symbol_table(symp))
            { 
                continue; 
            }

            // シンボル名が格納されているポインタをセット
            char *sym_name = head + strtab->sh_offset + symp->st_name;
            if(!strcmp(name, sym_name))
            {
                // nameとsym_nameが一致したら、ヒットしたオブジェクトファイル名と
                // シンボルのアドレスをセット
                obj->filename = objs[n].filename;
                obj->address = (char *)(head + shdr->sh_offset + symp->st_value);
                return 0;
            }
        }
    }
    return 1;
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
    
    if(symp->st_shndx == SHN_UNDEF || symp->st_shndx == SHN_ABS)
    {
        return falsE;
    }
    
    if(ELF64_ST_BIND(symp->st_info) != STB_GLOBAL)
    {
        return falsE;
    }

    if(get_sym_info_high(symp->st_info) != STB_GLOBAL)
    {
        return falsE;
    }

    if(get_sym_info_low(symp->st_info) != STT_NOTYPE ||
       get_sym_info_low(symp->st_info) != STT_OBJECT ||
       get_sym_info_low(symp->st_info) != STT_FUNC)
    {
        return falsE;
    }

    return 0; // true
}

u_int8_t get_sym_info_high(u_int8_t info)
{
    return info >> 4;
}

u_int8_t get_sym_info_low(u_int8_t info)
{
    return info << 4;

}

int relocate_common_symbol(Elf64_Ehdr *ehdr)
{
    int i;
    char *head;
    Elf64_Shdr *symtab;
    Elf64_Shdr *bss;
    Elf64_Sym *symp;

    symtab = get_section(ehdr, ".symtab");
    bss = get_section(ehdr, ".bss");
    head = (char *)ehdr;

    // symtabがシンボルテーブルのセクションか確認
    if(symtab->sh_entsize != sizeof(Elf64_Sym))
    {
        printf("[!!!] invalid entry size. (%ld)\n", symtab->sh_entsize);
        return 1;
    }

    int size_bss_sec = bss->sh_size;
    // .symtabセクションの場合、sh_entsizeの大きさの配列状のデータ構造であるので
    // .symtabセクションが終わるまで回して、各シンボル情報に対して解析を行う
    for(i = 0; i < symtab->sh_size; i += symtab->sh_entsize)
    {
        symp = (Elf64_Sym *)(head + symtab->sh_offset + i);
        if(symp->st_shndx != SHN_COMMON)
        {
            continue;
        }
        int align = symp->st_value - 1;
        size_bss_sec = (size_bss_sec + align) & ~align;
        // ↓ 違くない？
        symp->st_shndx = bss - (Elf64_Shdr *)(head + ehdr->e_shoff);
        symp->st_value = size_bss_sec;
        size_bss_sec += symp->st_size;
    }

    // 16bitでアラインメント
    size_bss_sec = (size_bss_sec + 15) & ~15;
    bss->sh_size = size_bss_sec;
    return 0;
}

int check_ehdr(Elf64_Ehdr *ehdr)
{
    if(ehdr->e_ident[1] == 0x45 &&
       ehdr->e_ident[2] == 0x4c &&
       ehdr->e_ident[3] == 0x46)
    {
        return 0;
    }
    return 1;
}

static int link_symbol(
    struct obj objs[], 
    int objnum, 
    Elf64_Ehdr *ehdr,
    Elf64_Shdr *reltab,
    Elf64_Shdr *defsec, // 再配置テーブルをもつセクション
    Elf64_Shdr *symtab,
    Elf64_Shdr *strtab)
{
    int i;
    int addr;
    int addend;
    char *head;
    unsigned int *addp;
    Elf64_Shdr *shdr;
    Elf64_Sym *symp;
    Elf64_Rel *relp;
    struct obj obj;

    // Elfファイルの先頭アドレス
    head = (char *)ehdr;
    
    // 再配置テーブルは配列状になっているので、配列分回す
    for(int i = 0; i < reltab->sh_size; i += reltab->sh_entsize)
    {
        // 再配置テーブルの各要素を取得する
        relp = (Elf64_Rel *)(head + reltab->sh_offset + i);
        
        // r_infoの上位24bitの情報(通し番号)に準じて
        // シンボルテーブルからシンボル情報を取得する
        symp = (Elf64_Sym *)(head + symtab->sh_offset + 
            (symtab->sh_entsize * ELF64_R_SYM(relp->r_info)));
        
        printf("%-10s ", objs[objnum].filename);

        if(symp->st_name)
        {
            // シンボル名を取得
            printf("%-12s ", head + strtab->sh_offset + symp->st_name);
        }
    }
}

int link_objs(struct obj objs[])
{
    int i;
    int j;
    char *name;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *reltab;
    Elf64_Shdr *defsec;
    Elf64_Shdr *symtab;
    Elf64_Shdr *strtab;

    printf("\nfilename  symbol  found  type addend  called defined  rel type\n");
    printf("---------- ------------ ---------- ---- -------- -------- -------- ------------\n");

    // オブジェクトファイル分回す
    for(i = 0; objs[i].filename; i++)
    {
        ehdr = (Elf64_Ehdr *)objs[i].address;
        symtab = get_section(ehdr, ".symtab");
        strtab = get_section(ehdr, ".strtab");

        // シンボルテーブルが格納されているセクション、または、
        // セクション名が格納されているセクションのどちらかがnullだったら、
        // このオブジェクトファイルに対するリンクは行わない
        if(!symtab || !strtab)
        {
            continue;
        }

        // 再配置テーブルを見るけるまで回す
        for(j = 0; j < ehdr->e_shnum; j++)
        {
            reltab = (Elf64_Shdr *)((char *)ehdr + ehdr->e_shoff + ehdr->e_shentsize * j);
            if(reltab->sh_type == SHT_REL || reltab->sh_type == SHT_RELA)
            {
                // 再配置テーブルが見つかったら、頭に.をつけて、セクションヘッダ(defsec)を取得
                name = get_section_name(ehdr, reltab);
                defsec = get_section(ehdr, strchr(name + 1, '.'));
                link_symbol(objs, i, ehdr, reltab, defsec, symtab, strtab);
            }
        }
    }
    return 0;
}