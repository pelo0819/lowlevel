# [step1]
# 挿入する関数をもつオブジェクトファイルを作成
gcc -c insert_func.c


# [step2]
# ターゲットのelfファイルに挿入する関数のバイナリを作成するelfファイルを作成
gcc make_func_binary.c -o make_func_binary
# 上のelfファイルを実行して挿入する関数のバイナリ(func_binary.dat)を吐き出す
./make_func_binary insert_func.o


# [step3]
# 関数を挿入されるプログラムのオブジェクトファイルを作成
gcc -c target_program.c

# func_binary.dat の中身を含んだオブジェクトファイルを作成
objcopy --add-section=bindata=func_binary.dat --set-section-flags=bindata=contents,alloc,load,readonly,data target_program.o inserted_target_program.o
# 関数の書き換えを行えるようなリンカスクリプトでelfファイルを作成
gcc inserted_target_program.o -o inserted_target_program -T text_elf_i386.x

# [step4]
# 実行 本来なら5が表示されたいが、77が表示されている
./inserted_target_program
