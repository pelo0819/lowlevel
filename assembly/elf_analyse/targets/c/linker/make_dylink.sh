DIR="target"
if [ $# -gt 0 ]; then
    DIR=$1
fi

$DIR/make_linker.sh $DIR

gcc -c dynlink.c -o dynlink.o
gcc -c linklib.c -o linklib.o
nasm -felf64 jump.asm -o jump.o

gcc dynlink.o linklib.o jump.o -o dynlink

../loader3/chflg_copy ./dynlink
chmod 777 ./dynlink_copy

./dynlink_copy sample_main $DIR/sample.o $DIR/sample2.o