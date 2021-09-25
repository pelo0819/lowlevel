gcc ../targets/c/addr/addr.c -c -o ../targets/c/addr/addr.o
gcc ../targets/c/addr/addr.o -o ../targets/c/addr/addr -T ../targets/c/linker_scripts/addr_elf_i386.x

../targets/c/addr/addr