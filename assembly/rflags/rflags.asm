;http://wisdom.sakura.ne.jp/programming/asm/assembly13.html
global _start

section .data
msg1: db 'yes', 10
msg2: db 'no', 10

section .text
_start:
        mov rax, 4
        ; raxが42より小さければjmp
        cmp rax, 42
        jl .yes
        jmp .no
.yes:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg1
        mov rdx, 4
        syscall
        jmp .con
.no:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg2
        mov rdx, 3
        syscall
.con:
        mov rax, 60
        xor rdi, rdi
        syscall


