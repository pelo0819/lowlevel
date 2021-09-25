global _start

section .data
codes: db '0123456789abcdef'
newline_char: db 10
message: db 'hello, world', 0

section .text

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
iterate_print_hex:
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

        jnz iterate_print_hex
        ret

strlen:
        xor rax, rax
iterate_strlen:
        cmp byte [rdi + rax], 0
        je end
        inc rax
        jmp iterate_strlen
end:
        ret

exit:
        mov rax, 60
        xor rdi, rdi
        syscall
        ret

_start:
        mov rdi, message
        call strlen
        mov rdi, rax
        call print_hex
        call print_newline
        call exit





