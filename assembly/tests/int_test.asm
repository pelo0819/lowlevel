%include "lib.asm"

section .data
msg_greater: db 'greater than 0', 0
msg_less: db 'less than 0', 0
section .bss
buffer: resb BUFFER_SIZE

section .text
global _start

_start: 
        mov rdi, -2147483648
        call print_int
        call print_newline
;        mov rdi, -1
;        cmp rdi, 0
;        call print_hex
;        call print_newline
;        mov rdi, -1
;        not rdi
;        call print_hex
;        call print_newline

;        jle jump_if_less
;
;        mov rdi, msg_greater
;        call print_string
;        jmp end_int_test
;
;jump_if_less:
;        mov rdi, msg_less
;        call print_string
;end_int_test:
        call exit




