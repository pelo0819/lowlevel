#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

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

    // ターゲットに挿入する関数を含むオブジェクトファイルを展開
    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    uint8_t *head = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    printf("ori head addr = %p\n", head);

    // 64bit移動する
    head += 64;
    printf("post head addr = %p\n", head);

    uint8_t buffer[15];
    memcpy(buffer, head, 15);

    FILE *file = NULL;
    file = fopen("func_binary.dat", "wb");
    fwrite(buffer, sizeof(uint8_t), sizeof(buffer)/sizeof(buffer[0]), file);
    fclose(file);

    printf("[*] output binary.\n");
    
    munmap(head, sb.st_size);
    close(fd);
    return 0;
}


