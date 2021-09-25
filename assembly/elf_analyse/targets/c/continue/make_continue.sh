nasm -felf64 down_lib.asm -o down_lib.o
gcc -c down.c -o down.o
gcc down.o down_lib.o -o down -static

# core dump を出力するように設定
ulimit -c unlimited
./down

gcc continue.c -o continue
./continue core