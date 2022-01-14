./esub "a.*b"  "\\"  "qabcabd" 2> test1.out
echo "Wrong regexp: \\ at the end of substitution" > test2.out
cmp test1.out test2.out

./esub "a.*b"  "\\\\"  "qabcabd" > test1.out
echo 'qabcabd' | sed -E 's/a.*b/\\/' > test2.out
cmp test1.out test2.out

./esub "a.*b"  ""  "qabcabd" > test1.out
echo 'qabcabd' | sed -E 's/a.*b//' > test2.out
cmp test1.out test2.out

./esub "(q.*b)(c.*d)"  "\2\1"  "qabcabd" > test1.out
echo 'qabcabd' | sed -E 's/(q.*b)(c.*d)/\2\1/' > test2.out
cmp test1.out test2.out

./esub "(q.*b)(c.*d)"  "\0"  "qabcabd" > test1.out
echo 'qabcabd' | sed -E 's/(q.*b)(c.*d)/\0/' > test2.out
cmp test1.out test2.out

./esub "(q.*b)(c.*d)"  "\2\1\3"  "qabcabd" 2> test1.out
echo "invalid reference \3" > test2.out
cmp test1.out test2.out

./esub "Z(q.*b)(c.*d)Z"  "\0"  "qabcabd" 2> test1.out
echo "No regexp match" > test2.out
cmp test1.out test2.out

rm -f test1.out test2.out
