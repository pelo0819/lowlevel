%include "lib.asm"

section .data
section .bss
buffer: resb BUFFER_SIZE

section .text
global _start

_start: 
        mov rdi, 4
        call mmap_anonymous
        push rax

        mov rdi, rax
        mov rsi, 4
        call input_words

        mov rdi, rax
        call print_string

        pop rdi
        mov rsi, 1024
        call rel_mem

        call exit




