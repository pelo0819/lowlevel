%include "def.asm"

section .data
newline_char: db 10
codes: db '0123456789abcdef'

case1: db 'case1', 0
case2: db 'case2', 0
case3: db 'case3', 0 

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

; 10進数の数字をバイナリで表示する
; arg -> rdi : 10進数の数字(上限値は255)
print_binary:
        push rcx
        push rdi
        mov rdi, 0x306200
        call print_char
        pop rdi
        mov rcx, 8
iterate_print_binary:
        push rdi        ; 元のrdiの値を退避
        dec rcx
        sar rdi, cl
        and rdi, 0x1

        push rcx
        call print_int
        pop rcx   
        pop rdi         ; 元のrdiを戻す
        test rcx, rcx
        jnz iterate_print_binary
        pop rcx
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
        call print_newline

        pop rdx
        pop rcx
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

; rdiに格納したuintを出力する
; arg -> rdi : 出力したいuint
print_uint:
        mov rsi, 19
        call print_positive_num
        ret

; rdiに格納したintを出力する
; arg -> rdi : 出力したいint       
print_int:
        push rdi        ; 出力したい数を退避
        cmp rdi, 0
        jl less_0_print_int
        jmp above_or_equal_0_print_int
less_0_print_int:
        mov rdi, 0x2d   ; 負の数なので'-'を出力
        call print_char
        pop rdi         ; 取り出す
        not rdi         ; 負の数なので、ビット反転
        inc rdi         ; 1足せば元の数
        jmp end_print_int
above_or_equal_0_print_int:
        pop rdi
end_print_int:
        mov rsi, 10     ; intの最大値は10桁
        call print_positive_num
        ret

; rdiに格納した正の数を出力する
; arg -> rdi : 出力したい正の数
;        rsi : rdiは10進数で何桁か
print_positive_num:
        push rbx
        push rdx
        mov rdx, rdi
iterate_print_positive_num:
        mov rdi, rdx
        call div10n     ; raxに商、rdxに余り
        push rdx        ; rdxをスタックに退避
        cmp rbx, 0      ; 出力済みフラグが立っているか確認
        ja yes_print_positive_num
        cmp rax, 0
                        ; 商が0以下なら出力しない
        jle not_print_positive_num
                        ; 商をasciiに変換
                        ; raxにasciiがセットされる
yes_print_positive_num:
        mov rdi, rax
        call int_2_ascii
        mov rdi, rax
        call print_char ; 変換した商を出力
        mov rbx, 1      ; rbxを一度でも出力した
                        ; フラグとみなし、そのフラグを立てる
not_print_positive_num:
        pop rdx         ; 余りをrdxに戻す
        sub rsi, 1      ; rsiから1引く
        cmp rsi, 0      ; rsiが0以上か確認
                        ; 0でないならループ続行
        ja iterate_print_positive_num
        
        mov rdi, rdx
        call int_2_ascii
        mov rdi, rax
        call print_char
        pop rdx
        pop rbx
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
input_words:
        push rdx
        mov rax, 0
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 0
        syscall

        mov rax, rsi

        pop rdx
        ret

; メモリを確保する(無名マッピング)
; arg -> rdi : 確保するメモリ幅(byte)
; ret -> rax : 確保したメモリの先頭アドレス
mmap_anonymous:
        push rsi
        mov rax, 9   ; mmapシステムコールをセット
        mov rsi, rdi ; メモリ幅をセット
        ; 確保するメモリの先頭アドレスをセット
        ; こだわりはないので0をセットし、OSに選択をゆだねる
        mov rdi, 0
        ; 保護フラグのセット、全部許す
        mov rdx, PROT_READ | PROT_WRITE | PROC_EXEC
        ; 動作フラグのセット、無名マッピングでプロセスで独立
        mov r10, MAP_PRIVATE | MAP_ANONYMOUS
        mov r9, 0
        syscall
        pop rsi
        ret

; メモリを開放する
; arg -> rdi : 開放するメモリの先頭アドレス
;        rsi : 確保するメモリ幅(byte)
; ret -> rax : 成功したら0,失敗なら-1
rel_mem:
        mov rax, 11 ; munmapシステムコールをセット
        ; 後は引数をそのまま使用するので実行
        syscall
        ret

; rdiに与えた先頭アドレスに格納される
; 文字列の中から数字を抜き取る
; arg -> rdi : 文字列の先頭アドレス
; ret -> rax : 抜き取った数字
parse_digits8:
        push rbx
        push rcx
        push rdx
        push r8
        push r9

        xor rbx, rbx    ; rbx : 数字部分の文字コードを格納する
        xor rcx, rcx    ; r11 : 数字部分の何文字目か
        xor rdx, rdx    ; rdx : 解析中の文字は何文字目か
        xor r8, r8      ; r8  : 一文字ずつの文字コードを格納する
        mov r9, rdi     ; r9  : 引数の先頭アドレスをコピー
        xor r11, r11    ; r11 : マイナスかそうかを識別するフラグ
iterate_parse_digits8:
        mov r8b, byte[r9 + rdx]
        ; 数字の文字コードから確認する
        cmp r8b, 0x30   ; まず0x30以上か確認
        jae above_or_equal_0x30_parse_digits8
        jmp not_digits_parse_digits8
above_or_equal_0x30_parse_digits8:
        cmp r8b, 0x39   ; 次に0x39以下か確認
        jle less_or_equal_0x39_parse_digits8
        jmp not_digits_parse_digits8
less_or_equal_0x39_parse_digits8:
        ; 数字ならばここを通る
        cmp rcx, 0      ; 初めての数字か確認
        ja shift_left_parse_digits8
        ; 初めての数字の場合
        jmp minus_check_parse_digits8
shift_left_parse_digits8:
        ; 2回目以降の数字ならここを通る
        sal rbx, 8      ; 左シフトする
minus_check_parse_digits8:
        cmp rdx, 0
        ; 数字が最初からある場合はマイナスはあり得ない
        jle add_digits_ascii_parse_digits8
        ; ひとつ前の文字がマイナスか確認
        mov al, byte[r9 + rdx -1]
        cmp al, 0x2d
        jne add_digits_ascii_parse_digits8
        ; ひとつ前の文字がマイナスならばここを通る
        mov r11, 1      ; マイナスフラグを立てる
add_digits_ascii_parse_digits8:
        mov bl, r8b
        inc rcx
        jmp prepare_next_parse_digits8
not_digits_parse_digits8:
        ; 数字でなければここを通る
        ; r11が0より大きいと数字から数字でない文字を
        ; 解析したことになるので終了
        cmp rcx, 0
        ja end_parse_digits8
prepare_next_parse_digits8:
        inc rdx
        cmp r8, 0
        ja iterate_parse_digits8
end_parse_digits8:
        mov rdi, rbx
        mov rsi, rcx
        call trans_digits_ascii_2_int

        cmp r11, 1
        je minus_parse_digits8
        jmp plus_parse_digits8
minus_parse_digits8:
        not rax         ; マイナスなので、ビット反転して
        inc rax         ; 1足してあげる
plus_parse_digits8:
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        ret

; rdiに文字コードで与えた数字を10進数にして戻す
; 8byteを上限とする
; 絶対に数字の文字コードを入れること
; arg -> rdi : 数字の文字コード
;        rsi : 文字数
; ret -> rax : 数字(10進数)
trans_digits_ascii_2_int:
        push rbx
        push rcx
        push rdx
        push r9
        push r10

        mov r9, rdi     ; r9に元の文字コードを退避
        mov rbx, rsi

        mov rdx, 8      ; rdxは1文字当たりのbit数をセット
        xor r10, r10    ; r10は返り値のバッファとして使用、0にする
iterate_trans_digits_ascii_2_int:
        push r9         ; 元の文字コードをスタックに退避
        
        sub rbx, 1      ; 何桁目 - 1 の値
        mov rax, 1      ; r9を何ビット右シフトするかを
        mov rdx, 8
        mul rdx         ; 決める、raxにその値をセット
        mul rbx         
        mov rcx, rax    ; rcxをraxにセット

        sar r9, cl      ; 右シフトする
        and r9, 0xff    ; 論理和とって下位8bit以外をクリア

        sub r9, 0x30    ; 0(0x30)を引く、残った値がその桁の値

        mov rdi, rbx    ; 10のn乗を算出する
        call pow10n
        mul r9           
        add r10, rax     

        pop r9          ; 元の文字コードをr9に戻す
        test rbx, rbx   ; まだループするか確認
        jnz iterate_trans_digits_ascii_2_int

        mov rax, r10    ; 帰り値をセット

        pop r10
        pop r9
        pop rdx
        pop rcx
        pop rbx
        ret

; 文字列が等しいか
; arg -> rdi : 対象1の先頭アドレス
;        rsi : 対象2の先頭アドレス
; ret -> rax : 同じなら1,違うなら0
string_equals:
        push r8
        push r9
        push rdx
        ; r8 : 対象1の解析中の1文字の文字コードのバッファ
        xor r8, r8
        ; r9 : 対象2の解析中の1文字の文字コードのバッファ
        xor r9, r9
        ; rdx : 何文字目を解析中か
        xor rdx, rdx
iterate_string_equals:
        mov r8b, byte[rdi + rdx]
        mov r9b, byte[rsi + rdx]

        ; r8とr9を比較、同じじゃないなら解析終了
        cmp r8b, r9b
        jne not_equal_string_equals

        inc rdx
        cmp r8, 0       ; ヌルチェック
        ; ヌルでないなら解析続行
        ja iterate_string_equals
        ; ここまでくるならr8=r9
        jmp equal_string_equals
not_equal_string_equals:
        mov rax, 0
        jmp end_string_equals
equal_string_equals:
        mov rax, 1
end_string_equals:
        pop rdx
        pop r9
        pop r8
        ret

; 文字列をコピーする
; arg -> rdi : コピー元のポインタ
;        rsi : コピー先のポインタ
;        rdx : コピー先のポインタのbyte数
string_copy:
        push rcx
        push r8
        ; コピー元の文字数とコピー先のポインタの
        ; 長さを比較、コピー先が小さければ失敗
        call string_length
        inc rax
        cmp rax, rdx
        ja fail_string_copy
        ; コピー中の文字数
        xor rcx, rcx
        ; コピー中の1文字の文字コード
        xor r8, r8
iterate_string_copy:
        xor r8, r8
        mov r8b, byte[rdi + rcx]
        ; 1文字コピーする
        mov byte[rsi + rcx], r8b
        inc rcx
        ; コピー元のヌルチェック
        cmp r8, 0
        ; コピー元はまだ文字が残っているので
        ; 次ループに進めるか確認
        ja iterate_string_copy
        jmp success_string_copy
success_string_copy:
        mov rax, rsi
        jmp end_string_copy
fail_string_copy:
        mov rax, 0
end_string_copy:
        pop r8
        pop rcx
        ret

; 終了処理
exit:
        mov rax, 60
        xor rdi, rdi
        syscall
        ret




