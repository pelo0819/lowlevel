GLOBAL pprint
;GLOBAL add
GLOBAL _start

extern main

SECTION .data
message: db 'hello, world', 10
newline_char: db 10

SECTION .text
_start:
        ;pop rdi ; argcをrdiにpop
        ;mov rsi, rsp ; 
        call main
        call exit
        ret

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

; 改行する
print_newline:
        push rdx
        push rcx

        mov rax, 1
        mov rdi, 1
        mov rsi, newline_char
        mov rdx, 1
        syscall
        
        pop rcx
        pop rdx
        ret

; 終了処理
exit:
        mov rax, 60
        xor rdi, rdi
        syscall
        ret



