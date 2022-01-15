GENERATES = move safe.so

move: move.c
	gcc $< -o $@

safe.so: safe.c
	gcc $< -shared -ldl -o $@

clean:
	rm -f $(GENERATES)