global _start

section .data
msg1: db 'jmp to one.', 10
msg2: db 'jmp to two.', 10
msg3: db 'jmp to thr.', 10

section .text
_start:
        mov rax, 1
        mov rbx, 1
        cmp rax, rbx
        jg .one
        jl .two
        jmp .thr
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
        mov rax, 1 ; writeシステムコールをセット
        mov rdi, 1 ; stdoutをセット
        mov rsi, msg3 ; 出力内容をセット
        mov rdx, 12 ; 出力byte数をセット
        syscall ; システムコール実行

        ; exitを実行
        mov rax, 60
        xor rdi, rdi
        syscall

