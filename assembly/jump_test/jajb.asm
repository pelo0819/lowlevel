global _start

section .data
msg1: db 'jmp to one.', 10
msg2: db 'jmp to two.', 10

section .text
_start:
        mov rax, 1
        mov rbx, 2
        cmp rax, rbx
        ja .one
        jb .two
.one:
        ; good byeを出力
        mov rax, 1 ; writeシステムコールをセット
        mov rdi, 1 ; stdoutをセット
        mov rsi, msg1 ; 出力内容をセット
        mov rdx, 12 ; 出力byte数をセット
        syscall ; システムコール実行
        jmp .thr
.two:
        mov rax, 1 ; writeシステムコールをセット
        mov rdi, 1 ; stdoutをセット
        mov rsi, msg2 ; 出力内容をセット
        mov rdx, 12 ; 出力byte数をセット
        syscall ; システムコール実行
.thr:
        ; exitを実行
        mov rax, 60
        xor rdi, rdi
        syscall

