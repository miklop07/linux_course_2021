echo "Md5 configure.ac" | ./rhasher | head -n 1 | awk '{print $2}' > test1
md5sum configure.ac | awk '{print $1}'> test2
cmp test1 test2

echo "ShA1 configure.ac" | ./rhasher | head -n 1 | awk '{print $2}' > test1
sha1sum configure.ac | awk '{print $1}'> test2
cmp test1 test2

echo "Md5 \"String_to_hash" | ./rhasher | head -n 1 | awk '{print $2}' > test1
echo -n "String_to_hash" | md5sum | awk '{print $1}'> test2
cmp test1 test2

echo "ShA1 \"String_to_hash" | ./rhasher | head -n 1 | awk '{print $2}' > test1
echo -n "String_to_hash" | sha1sum | awk '{print $1}'> test2
cmp test1 test2

rm -f test1 test2