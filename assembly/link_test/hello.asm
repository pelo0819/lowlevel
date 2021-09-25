extern print_msg2
extern print_msg3
extern exit

global _start

[section .data]
msg: db 'hello, wold', 10


[section .text]
_start:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg
        mov rdx, 14
        syscall


        call print_msg2
        call print_msg3
        call exit