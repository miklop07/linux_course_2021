LD_PRELOAD=./pre_lib.so strace -P _PROTECTED_ -e trace=read -e inject=read:error=EISDIR:when=2 ./move _PROTECTED_ mv
if [ $? -eq 21 ] && [ -f _PROTECTED_ ] && [ ! -f mv ]; then echo "OK"; else echo "FAILED"; fi

LD_PRELOAD=./pre_lib.so strace -P _PROTECTED_ -eclose -e fault=close:error=EBADF ./move _PROTECTED_ mv
if [ $? -eq 9 ] && [ -f _PROTECTED_ ] && [ ! -f mv ]; then echo "OK"; else echo "FAILED"; fi

LD_PRELOAD=./pre_lib.so strace -eclose -e fault=close:error=EBADF:when=5 ./move _PROTECTED_ mv
if [ $? -eq 9 ] && [ -f _PROTECTED_ ] && [ ! -f mv ]; then echo "OK"; else echo "FAILED"; fi

LD_PRELOAD=./pre_lib.so strace -e trace=write -e inject=write:error=EINVAL:when=1 ./move _PROTECTED_ mv
if [ $? -eq 22 ] && [ -f _PROTECTED_ ] && [ ! -f mv ]; then echo "OK"; else echo "FAILED"; fi

LD_PRELOAD=./pre_lib.so strace -P _PROTECTED_ -e trace=openat -e inject=openat:error=EFAULT ./move _PROTECTED_ mv
if [ $? -eq 14 ] && [ -f _PROTECTED_ ] && [ ! -f mv ]; then echo "OK"; else echo "FAILED"; fi

LD_PRELOAD=./pre_lib.so strace -P mv -e trace=openat -e inject=openat:error=EFAULT ./move _PROTECTED_ mv
if [ $? -eq 14 ] && [ -f _PROTECTED_ ] && [ ! -f mv ]; then echo "OK"; else echo "FAILED"; fi

strace -P _PROTECTED_ -e trace=read -e inject=read:error=EISDIR:when=2 ./move _PROTECTED_ _PROTECTED_mv
if [ $? -eq 21 ] && [ -f _PROTECTED_ ] && [ ! -f _PROTECTED_mv ]; then echo "OK"; else echo "FAILED"; fi

strace -P _PROTECTED_ -eclose -e fault=close:error=EBADF ./move _PROTECTED_ _PROTECTED_mv
if [ $? -eq 9 ] && [ -f _PROTECTED_ ] && [ ! -f _PROTECTED_mv ]; then echo "OK"; else echo "FAILED"; fi

