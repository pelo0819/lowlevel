#include "continue.h"

extern int set_regs(void *ptr);

void *get_note(void *head, int nt_type);
void print_reg(struct my_elf_prstatus *status);
u_int64_t roundup8bytes(u_int64_t v);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("[!!!] args is not enough.\n");
        return 1;
    }

    int fd;
    struct stat sb;
    void *head = NULL;
    static char file_name[128];

    strcpy(file_name, argv[1]);
    printf("[*] attempt to open file. (%s)\n", file_name);
    fd = open(file_name, O_RDONLY);
    if(fd < 0)
    {
        printf("[!!!] cannot open file. (%s)\n", file_name);
        return 1;
    }
    printf("[*] success open file. (%s)\n", file_name);

    fstat(fd, &sb);
    head = mmap(
        NULL, 
        sb.st_size, 
        PROT_READ, 
        MAP_SHARED, 
        fd, 
        0);
    
    struct my_elf_prstatus *note_status;
    note_status = get_note(head, NT_PRSTATUS);
    print_reg(note_status);

    close(fd);
    
    return 0;
}

void *get_note(void *head, int nt_type)
{
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)head;
    
    int i = 0;
    for(i = 0; i < ehdr->e_phnum; i++)
    {
        Elf64_Phdr *phdr = (head + ehdr->e_phoff + i * ehdr->e_phentsize);
        if(phdr->p_type != PT_NOTE)
        {
            continue;
        }
        void *table = (head + phdr->p_offset);
        void *end_hdr = (table + phdr->p_filesz);
        while(table < end_hdr)
        {
            Elf64_Nhdr *nhdr = (Elf64_Nhdr *)table;
            
            table += 3 * sizeof(Elf64_Word);
            table += roundup8bytes(nhdr->n_namesz);
            printf("n_namesz = %d\n", nhdr->n_namesz);
            printf("n_namesz(r) = %ld\n", roundup8bytes(nhdr->n_namesz));
            printf("n_descsz = %d\n", nhdr->n_descsz);
            printf("n_descsz(r) = %ld\n", roundup8bytes(nhdr->n_descsz));

            if(nhdr->n_type == nt_type)
            {
                return table;
            }

            table += roundup8bytes(nhdr->n_descsz);
        }
    }
    return 0;
}

void print_reg(struct my_elf_prstatus *status)
{
    //assert(status);
    printf("[*] show register info\n");
    printf("rax:0x%016llx, rbx:0x%016llx, rcx:0x%016llx, rdx:0x%016llx\n",
        status->pr_reg.rax, status->pr_reg.rbx, status->pr_reg.rcx, status->pr_reg.rdx);
    
    printf("rdi:0x%016llx, rsi:0x%016llx, r8 :0x%016llx, r9 :0x%016llx\n",
        status->pr_reg.rdi, status->pr_reg.rsi, status->pr_reg.r8, status->pr_reg.r9);
    
    printf("r10:0x%016llx, r11:0x%016llx, r12:0x%016llx, r13:0x%016llx\n",
        status->pr_reg.r10, status->pr_reg.r11, status->pr_reg.r12, status->pr_reg.r13);
    
    printf("r14:0x%016llx, r15:0x%016llx, rsp:0x%016llx, cs :0x%016llx\n",
        status->pr_reg.r14, status->pr_reg.r15, status->pr_reg.rsp, status->pr_reg.cs);
    
    printf("ds :0x%016llx, es :0x%016llx, fs :0x%016llx, gs :0x%016llx\n",
        status->pr_reg.ds, status->pr_reg.es, status->pr_reg.fs, status->pr_reg.gs);
    
    printf("eflags  :0x%016llx, orig_rax :0x%016llx\n",
        status->pr_reg.eflags, status->pr_reg.orig_rax);
    printf("fs_base :0x%016llx, gs_base  :0x%016llx\n",
        status->pr_reg.fs_base, status->pr_reg.gs_base);
}

/*
Note header の　n_namesz,n_descszは実際のsizeだけど、
dateは8bytes(64bits) alignmentされてるので丸める
*/
u_int64_t roundup8bytes(u_int64_t v)
{
    if(v % 8)
    {
        return v + 8 - v % 8;
    }
    return v;
}