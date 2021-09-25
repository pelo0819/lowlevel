; goal : raxに格納されている値を出力する

section .data

; グローバル変数としてcodesを定義
; 文字変換用
codes: db '0123456789ABCDEF'

section .text
global _start
_start:
        mov rax, 2
        mov rdi, 1
        mov rdx, 1 
        mov rcx, 16
.loop:
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
        jnz .loop

        mov rax, 60
        xor rdi, rdi
        syscall
