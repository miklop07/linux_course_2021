#!/bin/bash
DELAY=0
if [ $# -eq 1 ]; then
    DELAY=$1;
fi

TEXT=$(od -A n -t x1 -v)
X_POS=0; Y_POS=0; COORDS=""
for CHAR in $TEXT; do
    if [ "$CHAR" == "0a" ]; then
        Y_POS=$((Y_POS + 1))
        X_POS=0
    else
        X_POS=$((X_POS + 1))
        if [ "$CHAR" != "20" ]; then
            COORDS+="$X_POS $Y_POS $CHAR\n"
        fi
    fi
done

COORDS=$(echo -e "$COORDS" | shuf)

tput clear
echo "$COORDS" |
while read y x c; do
    if [ "$c" != "" ]; then
        tput cup $x $y
        echo -ne "\x$c"
    fi  
    if [ "$DELAY" != "0" ]; then
        sleep $DELAY;
    fi
done
tput cup $(tput lines) 0