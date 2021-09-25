gcc -c rasm.c -o rasm.o
gcc -c rasm2.c -o rasm2.o
gcc rasm.o rasm2.o -o rasm

objdump -d rasm.o > ./output/objdump_rasm_o.pelo
objdump -d rasm2.o > ./output/objdump_rasm2_o.pelo
objdump -d rasm > ./output/objdump_rasm.pelo

readelf -S -r -s rasm.o > ./output/readelf_rasm_o.pelo
readelf -S -r -s rasm2.o > ./output/readelf_rasm2_o.pelo
readelf -S -r -s rasm > ./output/readelf_rasm.pelo