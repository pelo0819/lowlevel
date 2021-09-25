#!/bin/bash

# c and object file
bit32="32"
path="../targets/c/overwrite/overwrite"
c_ext=".c"
o_ext=".o"
c_path="$path""$c_ext"
o_path="$path""$o_ext"

# linker script
ls_path=""
ls_path_32="../targets/c/linker_scripts/text_elf_i386_32.x"
ls_path_64="../targets/c/linker_scripts/text_elf_i386.x"

# invalid Data Execution Prevention(DEP)
invalid_dep="-z execstack"

# option commands
show_ls="-Wl,--verbose"

if [ $# -gt 0 -a $1 = $bit32 ]; then
    echo "compile 32bit"
    
    gcc -m32 "$c_path" -c -o "$o_path" "$invalid_dep"
    gcc -m32 "$o_path" -o "$path" -T "$ls_path_32"
else
    echo "compile 64bit"

    gcc "$c_path" -c -o "$o_path" "$invalid_dep"
    gcc "$o_path" -o "$path" -T "$ls_path_64"
fi

#ls -la ../targets/c/overwrite
#objdump -h -p ../targets/c/overwrite/overwrite
"$path"
