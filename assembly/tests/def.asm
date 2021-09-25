%define BUFFER_SIZE 128

; Flags openシステムコール実行時に必要
; 下記を組み合わせようね
%define O_APPEND 0x1000 ; 追加モード
%define O_CREATE 0x40   ; 新規作成
; ファイルが既に存在し、
; 通常ファイルで書込可の場合、長さを0にする
%define O_TRUNC  0x200  
%define O_RDONLY 0      ; 読込可
%define O_WRONLY 1      ; 書込可
%define O_RDWE   2      ; 読込書込可

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
