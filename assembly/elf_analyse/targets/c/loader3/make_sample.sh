
 echo [**] nasm -felf64 stdio.asm -o stdio.o
 nasm -felf64 stdio.asm -o stdio.o

 echo [**] gcc -c sample.c -o sample.o
 gcc -c sample.c -o sample.o

 
 echo [**] gcc sample.o stdio.o -o sample -static -T elf_i386_insert_empty_static.x
 gcc sample.o stdio.o -o sample -static -T elf_i386_insert_empty_static.x -nostdlib
 

