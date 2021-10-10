gcc -c dynlink.c -o dynlink.o
gcc -c linklib.c -o linklib.o

gcc dynlink.o linklib.o -o dynlink

./dynlink sample_main