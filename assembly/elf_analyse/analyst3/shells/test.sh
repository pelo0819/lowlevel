#1/bin/bash

bit64="64"

c_path="../targets/c/"
o_file="overwrite/"
ls "$c_path""$o_file"

str=""
str1="6664bit"
str2="3332bit"
if [ $1 = $bit64 ]; then
    str="$str1"
else
    str="$str2"
fi

echo "$str"