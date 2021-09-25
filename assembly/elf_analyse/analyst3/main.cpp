#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "ElfManager.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "args is not enough.\n");
        return 1;
    }

    int fd;
    int i;
    struct stat sb;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    uint8_t *head = static_cast<uint8_t *>(mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0));

    ElfManager *mgr = new ElfManager();
    mgr->SetElfHead(head);
    mgr->SetPrintMode(argc, argv);
    mgr->Analyse();
    
    munmap(head, sb.st_size);
    close(fd);

    delete mgr;
    return 0;
}
