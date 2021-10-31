DIR="."
if [ $# -gt 0 ]; then
    DIR=$1
fi

# assemble
nasm -felf64 $DIR/service.asm -o $DIR/service.o
gcc -c $DIR/main.c -o $DIR/main.o -fno-builtin
gcc -c $DIR/sample.c -o $DIR/sample.o -fno-builtin
gcc -c $DIR/sample2.c -o $DIR/sample2.o -fno-builtin
gcc -c $DIR/crt.c -o $DIR/crt.o -fno-builtin

# link
gcc $DIR/main.o $DIR/sample.o $DIR/sample2.o $DIR/service.o $DIR/crt.o -o $DIR/sample -nostdlib #-Wl,--verbose
# gcc main.o sample.o sample2.o service.o crt.o -o sample

readelf -S -r -s $DIR/service.o > $DIR/readelf_service_o.pelo
readelf -S -r -s $DIR/sample.o > $DIR/readelf_sample_o.pelo
readelf -S -r -s $DIR/sample2.o > $DIR/readelf_sample2_o.pelo
readelf -S -r -s $DIR/sample > $DIR/readelf_sample.pelo


objdump -d $DIR/service.o > $DIR/objdump_service_o.pelo
objdump -d $DIR/sample.o > $DIR/objdump_sample_o.pelo
objdump -d $DIR/sample2.o > $DIR/objdump_sample2_o.pelo
objdump -d $DIR/sample > $DIR/objdump_sample.pelo
 

