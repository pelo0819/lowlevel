gcc ../targets/c/const.c -c -o ../targets/c/const.o -static
gcc ../targets/c/const_sub.c -c -o ../targets/c/const_sub.o -static
gcc ../targets/c/const.o ../targets/c/const_sub.o -o ../targets/c/const
ls -la ../targets/c/