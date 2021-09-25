
echo compile chflg_copy
gcc chflg_copy.c -o chflg_copy 

echo 
echo make sample2_copy
./chflg_copy sample2

echo 
echo change mode sample2_copy
chmod 777 sample2_copy