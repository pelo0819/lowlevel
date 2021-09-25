%define BUFFER_SIZE 128

section .data
newline_char: db 10
codes: db '0123456789abcdef'
demo1: dq 0x223344556677aaee
demo2: db 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0xaa, 0xee
test: dq -1
;input_buffer: db -1

;section .bss
;input_buffer : resb BUFFER_SIZE

section .text
print_hex:
        push rdx
        push rcx
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
        
        pop rcx
        pop rdx
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
print_string:
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
        call print_newline
        ret

; rdiに格納した文字コードを出力する
; arg -> rdi : 出力したい文字コード
print_char:
        push rax
        push rcx
        push rdx
        push rsi
        ; 引数の文字コードをraxにセット
        mov rax, rdi
        mov rdi, 1
        mov rdx, 1
        mov rcx, 64

iterate_print_char:
        push rax        ; 元の文字コードをスタックに退避

        sub rcx, 8      ; 出力したい1文字が最下位bitに
        sar rax, cl     ; くるように右シフトする
        and rax, 0xff   ; 論理和とって下位8bit以外をクリア
        test rax, rax   ; raxがnullでないか確認
                        ; nullならシステムコールを実行しない 
        jz null_al_print_char

        push rax        ; al(出力したい1文字)をスタックにセット
        mov rsi, rsp    ; スタックポインタをrsiにセット
        mov rax, 1      ; writeシステムコールをセット
        mov rdi, 1      ; stdoutにセット
        mov rdx, 1      ; 1文字出力するようにセット

        push rcx        ; システムコールを実行するとrcx消えるのにスタックに退避
        syscall         ; 実行

        pop rcx         ; rcxを戻す
        pop rax         ; raxを戻す

null_al_print_char:
        pop rax
        
        test rcx, rcx
        jnz iterate_print_char

        pop rsi
        pop rdx
        pop rcx
        pop rax

        ret

; rdiに格納したuint8を出力する
; arg -> rdi : 出力したいuint
print_uint:
        push rsi
        push rbx
        push rdx
        mov rsi, 19     ; 10の19乗から始める
        mov rdx, rdi
iterate_print_unit:
        mov rdi, rdx
        call div10n     ; raxに商、rdxに余り
        push rdx        ; rdxをスタックに退避
        cmp rbx, 0      ; 出力済みフラグが立っているか確認
        ja yes_print_uint
        cmp rax, 0
                        ; 商が0以下なら出力しない
        jle not_print_uint
                        ; 商をasciiに変換
                        ; raxにasciiがセットされる
yes_print_uint:
        mov rdi, rax
        call int_2_ascii
        mov rdi, rax
        call print_char ; 変換した商を出力
        mov rbx, 1      ; rbxを一度でも出力した
                        ; フラグとみなし、そのフラグを立てる
not_print_uint:
        pop rdx         ; 余りをrdxに戻す
        sub rsi, 1      ; rsiから1引く
        cmp rsi, 0      ; rsiが0以上か確認
                        ; 0でないならループ続行
        ja iterate_print_unit
        
        mov rdi, rdx
        call int_2_ascii
        mov rdi, rax
        call print_char
        pop rdx
        pop rbx
        pop rsi
        ret

; 改行する
print_newline:
        push rdx

        mov rax, 1
        mov rdi, 1
        mov rsi, newline_char
        mov rdx, 1
        syscall
        
        pop rdx
        ret

; 10のn乗を計算する
; arg -> rdi : 何乗か
; ret -> rax : 結果
pow10n:
        cmp rdi, 0
        jle less_0_pow10n
        push rbx
        push rcx
        
        mov rcx, rdi
        mov rax, 1
        mov rbx, 10
iterate_power10n:
        mul rbx
        sub rcx, 1
        cmp rcx, 0
        ja iterate_power10n 
        
        pop rcx
        pop rbx
        jmp end_pow10n
less_0_pow10n:
        mov rax, 1
end_pow10n:
        ret

; 10のn乗で除算した時の商と余りを取得する
; arg -> rdi : 割る値, rsi : 何乗か
; ret -> rax : 商, rdx : 余り
div10n:
        push rbx

        push rdi        ; rdi(割られる値)をスタックにセット
        mov rdi, rsi
        call pow10n     ; 10のn乗をraxにセット
        mov rbx, rax    ; 割る値をrbxにセット    
        pop rdi         ; 割られる値をraxにセット
        mov rax, rdi    ; 割られる値をraxにセット
        div rbx
        
        pop rbx
        ret

; rdiにセットした一桁の数字のunicodeを取得する
; arg -> rdi : 一桁の数字
; ret -> rax : 一桁の数字のunicode
int_2_ascii:
        mov rax, 0x30   ; raxに'0'のasciiにセット
        add rax, rdi    ; raxにrdiを加算
        ret

; stdin用の関数
; arg -> rdi : stdinを受け付けるポインタ
;        rsi : サイズ
; ret -> rax : 入力された文字列のポインタ
read_word:
        push rdx
        mov rax, 0
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 0
        syscall

        mov rax, rsi

        pop rdx
        ret

; 終了処理
exit:
        mov rax, 60
        xor rdi, rdi
        syscall
        ret




