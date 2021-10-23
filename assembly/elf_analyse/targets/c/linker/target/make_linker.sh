
# assemble
nasm -felf64 service.asm -o service.o
gcc -c main.c -o main.o -fno-builtin
gcc -c sample.c -o sample.o -fno-builtin
gcc -c sample2.c -o sample2.o -fno-builtin
gcc -c crt.c -o crt.o -fno-builtin

# link
gcc main.o sample.o sample2.o service.o crt.o -o sample -nostdlib -Wl,--verbose
# gcc main.o sample.o sample2.o service.o crt.o -o sample

readelf -S -r -s service.o > readelf_service_o.pelo
readelf -S -r -s sample.o > readelf_sample_o.pelo
readelf -S -r -s sample2.o > readelf_sample2_o.pelo
readelf -S -r -s sample > readelf_sample.pelo


objdump -d service.o > objdump_service_o.pelo
objdump -d sample.o > objdump_sample_o.pelo
objdump -d sample2.o > objdump_sample2_o.pelo
objdump -d sample > objdump_sample.pelo
 

