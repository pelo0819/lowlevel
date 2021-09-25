%include "lib.asm"

section .data
msg_greater: db 'greater than 0', 0
msg_less: db 'less than 0', 0
msg : db 'hello duck tails', 0
msg2: db 'abcde', 0
section .bss
buffer: resb BUFFER_SIZE

section .text
global _start

_start: 
        ;mov rdi, msg_greater
        ;mov rdi, 0x3431363738
        ;mov rsi, 5
        mov rdi, msg
        ;mov rsi, msg2
        ;call string_equals

        mov rdi, 100
        call mmap_anonymous
        push rax

        mov rdi, msg
        mov rsi, rax
        mov rdx, 100
        call string_copy

        mov rdi, rax
        call print_string
        call print_newline

        pop rax
        mov rdi, 100
        call rel_mem

        ; mov rdi, 0x3031323334353637
        ; call print_char
        call exit




