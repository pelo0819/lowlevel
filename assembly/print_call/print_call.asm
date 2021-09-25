
section .data
newline_char: db 10
codes: db '0123456789abcdef'

msg1: db 'yes', 10

section .text
global _start

print_newline:
        mov rax, 1
        mov rdi, 1
        mov rsi, newline_char
        mov rdx, 1
        syscall
        ret

print_hex:
        mov rax, rdi
        mov rdi, 1
        mov rdx, 1
        mov rcx, 64
iterate:
        push rax

        sub rcx, 4
        sar rax, cl
        and rax, 0xf
        lea rsi, [codes + rax]

        mov rax, 1
        push rcx
        syscall

        pop rcx
        pop rax
        test rcx, rcx

        jnz iterate
        ret

exit:
        mov rax, 60
        xor rdi, rdi
        syscall
        ret

_start:
        mov rdi, 0x223344556677aaee

        call print_hex
        call print_newline
        call exit




