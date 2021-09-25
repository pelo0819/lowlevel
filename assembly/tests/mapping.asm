%include "lib.asm"

section .data
fname: db 'pelo', 0
neko: db 'nekodesu', 0
kuma: db 'kumadesu', 0

section .text
global _start

_start:
        mov rdi, 1024
        call mmap_anonymous

        push rax

        ; 確保メモリに値を代入(ab)
        mov qword[rax], 0x61
        mov qword[rax + 1], 0x62
        mov qword[rax + 2], 0xa

        mov rdi, rax
        call print_string

        pop rdi
        mov rsi, 1024
        call rel_mem

        mov rax, 0
        test rax, rax
        jnz not_zero

        mov rax, 1
        mov rdi, 1
        mov rsi, kuma
        mov rdx, 9
        syscall
not_zero:
        mov rax, 1
        mov rdi, 1
        mov rsi, neko
        mov rdx, 9
        syscall
        
        call exit




