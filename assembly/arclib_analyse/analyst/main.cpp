#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <ar.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#include "ElfManager.h"

#define SIZE_AR_NAME 16
#define SIZE_AR_DATE 12
#define SIZE_AR_UID  6
#define SIZE_AR_GID  6
#define SIZE_AR_MODE 8
#define SIZE_AR_SIZE 10

void mold_ar_info(char *after, char *before, int size);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "args is not enough.\n");
        return 1;
    }
    int fd;
    struct stat sb;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    // 開いたファイルの先頭アドレス
    uint8_t *head = static_cast<uint8_t *>(mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0));

    if(memcmp(head, ARMAG, SARMAG))
    {
        printf("this is not archive library file\n");
        return 1;
    }

    ElfManager *eMgr = new ElfManager();
    eMgr->SetPrintMode(argc, argv);

    int size = 0;
    // 開いたファイルの先頭アドレスからSARMAG分移動したアドレスから
    // (一番最初の)arヘッダを取得
    // SARMAG = 8 = !<arch>\n = archive　library fileであるための情報
    ar_hdr *p_arhdr = (ar_hdr *)(head + SARMAG);
    // オブジェクトファイル名を格納しているarヘッダ
    ar_hdr *p_name_arhdr = NULL;
    uint8_t *end_file = head + sb.st_size;
    while(true)
    {
        size = atoi(p_arhdr->ar_size);
        // arヘッダがアーカイブシンボルテーブルだったら
        if(!memcmp(p_arhdr->ar_name, "/ ", 2))
        {
            printf("symbol table found\n");
        }
        // arヘッダがファイル名格納用だったら
        else if(!memcmp(p_arhdr->ar_name, "//", 2))
        {
            printf("file_name table found\n");
            p_name_arhdr = p_arhdr;
        }
        else
        {
            char *fname = NULL;
            // arヘッダのサイズ
            uint8_t size_ar_hdr = (uint8_t)sizeof(struct ar_hdr);
            // ar_nameの頭文字が/ならば、ファイル名は
            // ファイル名格納用のarヘッダ内にある
            if(p_arhdr->ar_name[0] == '/')
            {
                fname = (char *)p_name_arhdr + size_ar_hdr +
                        atoi(&p_arhdr->ar_name[1]);
            }
            else
            {
                fname = p_arhdr->ar_name;
            }

            char *ptr = strchr(fname, '/');
            uint64_t diff = ptr - fname;
            char name[diff + 1];
            mold_ar_info(name, fname, diff);
            printf("found: %s, size: %d\n", name, size);

            eMgr->SetElfHead((uint8_t *)p_arhdr + sizeof(struct ar_hdr));
            eMgr->Analyse();
#if false
            // arヘッダの情報を出力
            // arヘッダのフォーマット上、NULL終端ないのでいちいち入れてる
            
            // ファイル名、ファイルサイズ
            char *ptr = strchr(fname, '/');
            uint64_t diff = ptr - fname;
            char name[diff + 1];
            mold_ar_info(name, fname, diff);
            printf("name:%s, size: %d\n", name, size);
            
            // ファイルの中身
            char content[size + 1];
            char *head_content = (char *)p_arhdr + size_ar_hdr;
            mold_ar_info(content, head_content, size);
            printf("content:%s", content);

            char date[SIZE_AR_DATE + 1];
            mold_ar_info(date, p_arhdr->ar_date, SIZE_AR_DATE);
            printf("date:%s\n", date);

            char uid[SIZE_AR_UID + 1];
            mold_ar_info(uid, p_arhdr->ar_gid, SIZE_AR_UID);
            printf("uid:%s\n", uid);

            char gid[SIZE_AR_GID + 1];
            mold_ar_info(gid, p_arhdr->ar_gid, SIZE_AR_GID);
            printf("gid:%s\n", gid);

            char mode[SIZE_AR_MODE + 1];
            mold_ar_info(mode, p_arhdr->ar_mode, SIZE_AR_MODE);
            printf("mode:%s\n", mode);

            printf("\n");
#endif
        }

        if(size % 2){ size++; }
        p_arhdr = (ar_hdr *)((uint8_t *)p_arhdr + sizeof(ar_hdr) + size);
        if((uint8_t *)p_arhdr >= end_file){ break; }
    }

    munmap(head, sb.st_size);
    close(fd);
    printf("end\n");
    delete eMgr;
    return 0;
}

void mold_ar_info(char *after, char *before, int size)
{
    strncpy(after, before, size);
    after[size] = '\0';
}

