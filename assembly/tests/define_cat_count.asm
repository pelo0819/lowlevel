BITS 64
%include "lib.asm"
%define cat_count 42

%macro test 2
%1 : db %2, 0
%endmacro

section .data
test msg, 'hello world'
msg2: db 'goodbye', 0
nums: db 0b11111111

%define x 5


section .text
global _start

_start:
%if x == 10
        mov rax, 100
%elif x==15
        mov rax, 115
%else
        mov rax, 200
%endif
        mov rdi, rax
        call print_int
        call print_newline

        mov rdi, nums
        call print_int
        call print_newline

        mov rdi, 200
        call print_binary
        call print_newline

        mov rdi, 0x306200
        call print_char
        call print_newline

        mov rdi, 0x

        call exit







