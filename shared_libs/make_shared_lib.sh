rm main
gcc -fpic -c sample.c -o sample_pic.o
gcc -shared sample_pic.o -o libsample.so.1
gcc -c main.c -o main.o -I.
gcc main.o -Wl,-rpath=. -L. -lsample -o main -T linker_script.x
readelf -a libsample.so > ./readelf_libsample_so.pelo
readelf -a main.o > ./readelf_main_o.pelo
readelf -a main > ./readelf_main.pelo
objdump -d libsample.so > ./objdump_libsample_so.pelo
objdump -d main.o > ./objdump_main_o.pelo
objdump -d main > ./objdump_main.pelo