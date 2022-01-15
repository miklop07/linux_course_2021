GENERATES = move pre_lib.so _not_protected_ _not_protected_mv _PROTECTED_ _PROTECTED_mv

test: move pre_lib.so
	date | cat > _not_protected_
	date | cat > _PROTECTED_
	LD_PRELOAD=./pre_lib.so ./move _not_protected_ _not_protected_mv
	LD_PRELOAD=./pre_lib.so ./move _PROTECTED_ _PROTECTED_mv
	if [ -f _PROTECTED_ ] && [ ! -f _not_protected_ ] && [ -f _not_protected_mv ] && [ -f _PROTECTED_mv ]; then echo "OK"; else echo "FAILED"; fi
	cmp _PROTECTED_ _PROTECTED_mv
	rm -f _PROTECTED_mv
	./tests.sh

move: move.c
	gcc $< -O0 -o $@

pre_lib.so: pre_lib.c
	gcc $< -shared -ldl -o $@

clean:
	rm -f $(GENERATES)
