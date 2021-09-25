global _start

section .data
message: db 'hello, world', 10

section .text
_start:
        mov rax, 2
        mod rdi, 1
        mov rsi, message
        mov rdx, 14
        syscall




