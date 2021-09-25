## すぐ忘れるのでgccコマンドのメモ

- 自前リンカスクリプトを使う場合  
 `gcc ../targets/c/const.o ../targets/c/const_sub.o -o ../targets/c/noconst -T /root/windows_disk/linux_libs/noconst_elf_i386_2.x`  
 `-T`以降に自前リンカスクリプトのパスを入れる

- 自前リンカスクリプトを作る場合
`gcc ../targets/c/const.o ../targets/c/const_sub.o -o ../targets/c/noconst -Wl,--verbose`  
`-Wl,--verbose`がリンク時に使用されているリンカスクリプトを表示するオプションなので、  
`using external linker script:`以下の部分をコピペして好きなように変更する   

- 共有ライブラリを実行ファイルに含む場合  
`-static`をつける  
`-static`をつけてよいことは、仮にポインタを表示する実行ファイル(`/root/windows_disk/assembly/symbol_resolve_test/array_and_pointer/pointer`)を実行した場合に、    
表示される値と`nm`コマンドでのシンボル位置が一致すること  