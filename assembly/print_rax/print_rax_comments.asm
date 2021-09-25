; goal : raxに格納されている値を出力する

section .data

; グローバル変数としてcodesを定義
; 文字変換用
codes: db '0123456789ABCDEF'

section .text
global _start
_start:
        ; 出力したい内容(16進数)
        ; raxに0x8888をセット
        ; 2進数だと0b1000100010001000
        mov rax, 0x8888
        ; writeシステムコールを実行するため、
        ; rdiにstdout(=1)をセット
        ; rdxに出力するbyte数をセット
        ; 最後まで見るとrdi,rdxは変更していない
        mov rdi, 1
        mov rdx, 1 
        ; 出力したいのは8888の4文字
        ; 1文字4bitなので16をrcxにセット
        mov rcx, 16
.loop:
        ; スタックにrax(元の文字列0x8888)を退避
        push rax
        ; rcxを-4する、1週目だと12
        sub rcx, 4
        ; 1週目だとraxを12ビット右シフトする
        ; 1週目だとraxは0b1000
        sar rax, cl
        ; 0b1000 (1週目なら)
        ; 0b1111 の論理和をとって
        ; 0b1000
        and rax, 0xf
        ; codesのアドレスからrax分(1週目なら8)進んだ
        ; アドレスをrsiにセット、つまり'8'のアドレス
        lea rsi, [codes + rax]
        ; writeシステムコール実行準備のため、
        ; raxに1をセット、1はwriteのディスクリプタ
        mov rax, 1
        ; システムコールを実行すると
        ; rcx,r11が変更されるかつ
        ; rcxに格納している値はraxを何bit算術右シフト
        ; するかを格納しており、まだ使いたいので、
        ; スタックに退避
        push rcx
        ; writeシステムコールを実行
        syscall
        ; rcx, raxをスタックから戻す
        pop rcx
        pop rax
        ; rcxが0でないなら、.loopラベルまでジャンプ
        test rcx, rcx
        jnz .loop

        ; ここに来たということは、
        ; 全部出力したので、exitシステムコールを実行
        mov rax, 60
        xor rdi, rdi
        syscall
