global _start

section .data
message: db 'hello, world', 10
msg: db 'neko', 10
msg2: db 'kuma', 10

section .text
_start:
        ; hello worldを出力
        mov rax, 1
        mov rdi, 1
        mov rsi, message
        mov rdx, 13
        syscall

        mov rdx, 1
        ; xor rdx, rdx
        ; rdxが0以外なら.kumaラベルまでジャンプ
        test rdx, rdx
        jnz .kuma

.neko:
        ; good byeを出力
        mov rax, 1
        mov rdi, 1
        mov rsi, msg
        mov rdx, 5
        syscall
.kuma:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg2
        mov rdx, 5
        syscall

        ; exitを実行
        mov rax, 60
        xor rdi, rdi
        syscall

