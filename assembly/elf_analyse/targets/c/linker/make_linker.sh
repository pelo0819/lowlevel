
# assemble
nasm -felf64 service.asm -o service.o
gcc -c main.c -o main.o -fno-builtin
gcc -c sample.c -o sample.o -fno-builtin
gcc -c sample2.c -o sample2.o -fno-builtin
gcc -c crt.c -o crt.o -fno-builtin

# link
# gcc main.o sample.o sample2.o service.o crt.o -o sample -nostdlib
gcc main.o sample.o sample2.o service.o crt.o -o sample
 

