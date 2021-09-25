; 保護フラグ、mmapシステムコール実行時に必要
%define PROC_EXEC  0x4 ; 実行可
%define PROT_READ  0x1 ; 読込可
%define PROT_WRITE 0x2 ; 書込可
%define PROT_NONE  0x0 ; アクセス不可

; 動作フラグ、mmapシステムコール実行時に必要
%define MAP_PRIVATE   0x1  ; プロセス間で共有可
%define MAP_SHARE     0x2  ; プレセスで独立
%define MAP_ANONYMOUS 0x20 ; 無名マッピングするか
%define MAP_FIXED     0x10 ; 知らん

global mmap_anonymous
global rel_mem
global set_mem

section .bss

section .data

section .text
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

set_mem:
        mov byte[rdi], 4
        mov word[rdi + 1], 6
        ret




