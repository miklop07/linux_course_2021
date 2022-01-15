LD_PRELOAD=./pre_lib.so strace -P _PROTECTED_ -e trace=read -e inject=read:error=EISDIR:when=2 ./move _PROTECTED_ _PROTECTED_mv
echo $?
if [ $? -eq 21 ] && [ -f _PROTECTED_ ] && [ ! -f _PROTECTED_mv ]; then echo "OK"; else echo "FAILED"; fi
