GLOBAL say
GLOBAL add
GLOBAL jump
GLOBAL ppush

SECTION .data
message: db 'hello, world', 10

SECTION .text
say:
        mov rax, 1
        mov rdi, 1
        mov rsi, message
        mov rdx, 14
        syscall

        ret

add:
        mov rax, rdi
        add rax, rsi
        ret

ppush:
        push rdi
        ret

jump:
        mov rax, rdi
        ;jmp rax
        call rax
        ret
