DIR="./static"

# echo [**] gcc -c loader.c -o loader.o 
gcc -c loader.c -o loader.o

# echo [**] nasm -felf64 jump.asm -jump.o 
nasm -felf64 jump.asm -o jump.o

# echo [**] gcc loader.o jump.o -o loader -T loader_elf_i386_static.x
gcc loader.o jump.o -o loader -T loader_elf_i386_static.x -ldl

# echo [**] gcc chflg_copy.c -o chflg_copy
gcc chflg_copy.c -o chflg_copy

# echo [**] ./chflg_copy loader
echo '=====> ./chflg_copy loader'
./chflg_copy loader

# echo [**] ./make_sample.sh
./static/make_sample.sh

# echo [**] chmod 777 loader_copy
chmod 777 loader_copy

readelf -a loader_copy > readelf_loader_copy.pelo
readelf -a loader > readelf_loader.pelo

echo 
# echo [**] ./loader_copy sample
echo '=====> ./loader_copy'
./loader_copy $DIR/sample abcf aaaa
# ./loader_copy $DIR/test