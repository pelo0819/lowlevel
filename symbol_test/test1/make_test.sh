gcc test.c -c -o test.o
gcc test.o -o test -static

readelf -S -r -s test.o > readelf_test_o.pelo
objdump -d test.o > objdump_test_o.pelo
readelf -S -r -s test > readelf_test.pelo
objdump -d test > objdump_test.pelo
