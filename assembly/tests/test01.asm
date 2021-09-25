%include "lib.asm"
global _start

section .bss
input_buffer : resb 64

section .data
;codes: db '0123456789abcdef'
message: db 'hello, world', 0
msg: db 0x61, 10
input_test: dq -1

section .text
_start:
        mov qword[input_test], 0x61
        mov qword[input_test + 1], 0x62
        mov qword[input_test + 2], 0x63
        mov qword[input_test + 3], 0xa
        mov rdi, [input_test]

        call print_hex
        call print_newline

        mov rax, 1
        mov rdi, 1
        mov rsi, input_test
        mov rdx, 4
        syscall
        
        call exit




