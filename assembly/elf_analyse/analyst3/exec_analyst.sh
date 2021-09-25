DIR_BASE="/root/windows_disk/assembly/elf_analyse"
DIR_ANALYST=$DIR_BASE"/analyst3/analyst"
DIR_TARGET=$DIR_BASE"/targets/c/"
FN_TARGET="/binary_insert/insert_func.o"
DIR_OUTPUT=$DIR_BASE"/analyst3/output/"
FN_OUTPUT="binary_insert.pelo"

if [ $# -ge 1 ]; then
    FN_TARGET=$1
fi

if [ $# -ge 2 ]; then
    FN_OUTPUT=$2
fi

$DIR_ANALYST $DIR_TARGET$FN_TARGET > $DIR_OUTPUT$FN_OUTPUT