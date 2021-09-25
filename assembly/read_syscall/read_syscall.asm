%include "lib.asm"
global _start

section .bss
input_buffer : resb 64

section .data
;codes: db '0123456789abcdef'
message: db 'hello, world', 0
msg: db 0x61, 10
input_test: db -1

section .text
_start:
        mov byte[input_test], 1
        mov rdi, input_test
        call print_hex
        call print_newline

        ;mov rdi, input_buffer
        ;mov rsi, 4
        ;call read_word

        ;mov rdi, rax
        ;mov rax, 0
        ;mov rdi, 0
        ;mov rsi, input_buffer
        ;mov rdx, 64
        ;syscall

        ;mov rdi, rsi
        ;call print_string

        mov rdi, 7
        mov rsi, 1
        call div10n
        mov rdi, rax
        call print_hex
        call print_newline
        mov rdi, rdx
        call print_hex
        call print_newline


        mov rdi, 9876543210
        call print_uint
        call print_newline
        ;mov rdi, 0x616263646566670a
        ;mov rdi, 0x63646566670a
        ;call print_char
        ;call print_newline

        ;mov rax, 2
        ;mov rbx, 5
        ;mul rbx

        mov rdi, 9
        call int_2_ascii
        mov rdi, rax
        call print_char
        call print_newline

        mov rdi, 1002
        mov rsi, 2
        ;div rcx
        call div10n

        mov rdi, rax
        call print_hex
        call print_newline
        

        mov rdi, rdx
        call print_hex
        call print_newline

        ;mov rax, 1
        ;mov rdi, 1

        ;mov rdi, 0x0a61626364656667
        ;mov rdi, 0x0a616263646
        ;mov rdi, 0x6161626364656667
        ;sar rdi, 56
        ;push rdi
        ;mov rsi, rsp
        ;push 3
        ;pop rdx
        ;mov rdi, 1
        ;mov rdx, 1
        ;syscall

        ;call print_hex

        ;pop rdi
        ;call print_hex
        ;call print_newline

        ;mov rdi, 0x61
        ;lea rsi, [rdi]
        ;mov rax, 1
        ;mov rdi, 1
        ;mov rdx, 3

        ;mov rdi, message
        ;call print_string
        call exit




