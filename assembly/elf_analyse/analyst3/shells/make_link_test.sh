gcc ../targets/c/linksamp/main.c -c -o ../targets/c/linksamp/main.o
gcc ../targets/c/linksamp/lib1.c -c -o ../targets/c/linksamp/lib1.o
gcc ../targets/c/linksamp/lib2.c -c -o ../targets/c/linksamp/lib2.o
#gcc ../targets/c/linksamp/main.o ../targets/c/linksamp/lib1.o ../targets/c/linksamp/lib2.o -o ../targets/c/linksamp/otherscr -T ../targets/c/linker_scripts/text_elf_i386.x
gcc ../targets/c/linksamp/main.o ../targets/c/linksamp/lib1.o ../targets/c/linksamp/lib2.o -o ../targets/c/linksamp/otherscr -T ../targets/c/linker_scripts/sample.lds
ls -la ../targets/c/linksamp
#objdump -h -p ../targets/c/linksamp/otherscr
../targets/c/linksamp/otherscr