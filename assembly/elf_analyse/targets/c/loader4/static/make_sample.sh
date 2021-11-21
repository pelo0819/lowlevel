DIR="./static"

# echo [**] nasm -felf64 stdio.asm -o stdio.o
nasm -felf64 $DIR/stdio.asm -o $DIR/stdio.o

# echo [**] gcc -c sample.c -o sample.o
gcc -c $DIR/sample.c -o $DIR/sample.o

gcc -fpic -c $DIR/sample_lib.c -o $DIR/sample_lib.o
gcc -shared $DIR/sample_lib.o -o $DIR/libsample.so.1
 
# echo [**] gcc sample.o stdio.o -o sample -T elf_i386_insert_empty_static.x
# gcc $DIR/sample.o $DIR/stdio.o -o $DIR/sample -T $DIR/elf_i386_insert_empty_static.x -nostdlib
gcc $DIR/sample.o $DIR/stdio.o -o $DIR/sample -T $DIR/elf_i386_insert_empty_static.x -Wl,-rpath=$DIR/ -L$DIR/ -lsample
 
readelf -a $DIR/sample > $DIR/readelf_sample.pelo
objdump -d $DIR/sample > $DIR/objdump_sample.pelo

readelf -a $DIR/libsample.so.1 > $DIR/readelf_libsample_so.pelo
objdump -d $DIR/libsample.so.1 > $DIR/objdump_libsample_so.pelo
