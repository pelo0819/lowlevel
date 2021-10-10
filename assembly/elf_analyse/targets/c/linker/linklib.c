#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <elf.h>

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
    void *head;
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
            printf("[!!!] invalid entry size. (%d)\n", symtab->sh_entsize);
            return -1;
        }

        for(i = 0; i < symtab->)


    }


    return 0;
}

int relocate_common_symbol(Elf64_Ehdr *ehdr)
{
    return 0;
}

int check_ehdr(Elf64_Ehdr *ehdr)
{
    return 0;
}

int link_objs(struct obj objs[])
{
    return 0;
}