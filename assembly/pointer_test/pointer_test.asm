
section .data
newline_char: db 10
codes: db '0123456789abcdef'
demo1: dq 0x223344556677aaee
demo2: db 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0xaa, 0xee
test: dq -1

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
        mov rdi, [test]
        call print_hex
        call print_newline

        mov byte[test], 1
        mov rdi, [test]
        call print_hex
        call print_newline

        mov word[test], 2
        mov rdi, [test]
        call print_hex
        call print_newline

        mov dword[test], 1
        mov rdi, [test]
        call print_hex
        call print_newline

        mov qword[test], 1
        mov rdi, [test]
        call print_hex
        call print_newline

        call exit




