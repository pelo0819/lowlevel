global _start
global pprint
global pexit
global pprint2

extern main

[section .data]

[section .text]
_start:
        ; osカーネルがコマンドライン引数を
        ; 設定した状態でプロセスが始まる
        pop rdi ; argcをrdiにpop
        mov rsi, rsp ; 
        call main
        call pexit

; nullで終わる文字列ポインタの文字列の長さを取得する
; arg -> rdi : ポインタ
; ret -> rax : 文字列の長さ
string_length:
        xor rax, rax
iterate_strlen:
        cmp byte [rdi + rax], 0
        je end
        inc rax
        jmp iterate_strlen
end:
        ret

; nullで終わる文字列ポインタの中身を出力する
; arg -> rdi : ポインタ
pprint:
        push rcx
        push rdx
        ; 文字列ポインタをrsiにセット
        mov rsi, rdi
        ; 文字列の長さを取得
        ; raxに書くのされているので、
        ; rdxに代入
        call string_length
        mov rdx, rax
        mov rax, 1
        mov rdi, 1
        syscall
        ;call print_newline

        pop rdx
        pop rcx
        ret

; 文字を出力する
; arg -> rdi : ポインタ
; arg -> rsi : 出力文字数
pprint2:
        mov rax, 1
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 1      
        syscall
        ret

; 終了処理
pexit:
        mov rax, 60
        xor rdi, rdi
        syscall
        ret
