
 echo [**] nasm -felf64 myprint.asm -o myprint.o
 nasm -felf64 myprint.asm -o myprint.o

 echo [**] gcc -c sample.c -o sample2.o
 gcc -c sample.c -o sample2.o

 echo [**] gcc sample2.o myprint.o -o sample2 -static -T elf_i386_insert_empty_static.x
 gcc sample2.o myprint.o -o sample2 -static -T elf_i386_insert_empty_static.x
 
#  ./sample2

