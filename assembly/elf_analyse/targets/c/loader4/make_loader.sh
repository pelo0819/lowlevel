echo [**] gcc -c loader.c -o loader.o 
gcc -c loader.c -o loader.o

echo [**] gcc loader.o jump.o -o loader -static -T loader_elf_i386_static.x
gcc loader.o jump.o -o loader -T loader_elf_i386_static.x

echo [**] ./chflg_copy loader
./chflg_copy loader
#./chflg_copy sample2

echo [**] ./make_sample.sh
./make_sample.sh

# nm sample2 | grep "T main" | sed 's/0000000000//' | sed 's/T main//' | sed -e 's/^/0x/' > main_addr.txt
# echo [**] nm sample | grep "T main" | sed 's/0000000000//' | sed 's/T makin//' > main_addr.txt 
# nm sample | grep "T main" | sed 's/0000000000//' | sed 's/T main//' > main_addr.txt

echo [**] chmod 777 loader_copy sample2_copy
chmod 777 loader_copy sample2_copy

echo [**] ./loader_copy sample
./loader_copy sample aaa