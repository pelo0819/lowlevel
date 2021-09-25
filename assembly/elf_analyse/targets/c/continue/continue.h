#ifndef CONTINUE_H
#define CONTINUE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/procfs.h>

struct regs_struct{
    unsigned long long int r15;
    unsigned long long int r14;
    unsigned long long int r13;
    unsigned long long int r12;
    unsigned long long int rbp;
    unsigned long long int rbx;
    unsigned long long int r11;
    unsigned long long int r10;
    unsigned long long int r9;
    unsigned long long int r8;
    unsigned long long int rax;
    unsigned long long int rcx;
    unsigned long long int rdx;
    unsigned long long int rsi;
    unsigned long long int rdi;
    unsigned long long int orig_rax;
    unsigned long long int rip;
    unsigned long long int cs;
    unsigned long long int eflags;
    unsigned long long int rsp;
    unsigned long long int ss;
    unsigned long long int fs_base;
    unsigned long long int gs_base;
    unsigned long long int ds;
    unsigned long long int es;
    unsigned long long int fs;
    unsigned long long int gs;
};


struct my_elf_prstatus{
    struct elf_siginfo pr_info; /* Info associated with signal */
    short       pr_cursig;              /* Current signal */
    unsigned long pr_sigpend;   /* Set of pending signals */
    unsigned long pr_sighold;   /* Set of held signals */
    pid_t       pr_pid;
    pid_t       pr_ppid;
    pid_t       pr_pgrp;
    pid_t       pr_sid;
    struct timeval pr_utime;    /* User time */
    struct timeval pr_stime;    /* System time */
    struct timeval pr_cutime;   /* Cumulative user time */
    struct timeval pr_cstime;   /* Cumulative system time */
    struct regs_struct pr_reg;
    int pr_fpvalid;             /* True if math co-processor being used.  */
};

#endif