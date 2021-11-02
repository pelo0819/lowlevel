gcc test.c -c -o test.o
gcc test.o -o test

readelf -a test.o > readelf_test_o.pelo
objdump -d test.o > objdump_test_o.pelo
readelf -a test > readelf_test.pelo
objdump -d test > objdump_test.pelo

DIR="../../dynamic_linker"
gcc -c $DIR/dynlink.c -o $DIR/dynlink.o
gcc -c $DIR/linklib.c -o $DIR/linklib.o
nasm -felf64 $DIR/jump.asm -o $DIR/jump.o

gcc $DIR/dynlink.o $DIR/linklib.o $DIR/jump.o -o $DIR/dynlink

../../assembly/elf_analyse/targets/c/loader3/chflg_copy $DIR/dynlink
chmod 777 $DIR/dynlink_copy

$DIR/dynlink_copy main ./test
# $DIR/dynlink_copy sample_main $DIR/target/sample.o $DIR/target/sample2.o $DIR/target/service.o
# $DIR/dynlink_copy sample_main $DIR/target/sample