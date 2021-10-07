GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ o.* test_*
CFLAGS = -Wall

all: README prog prog-a prog-so



test: prog prog-a prog-so
	/bin/bash -c "(exec -a prog ./prog)" 2> test_null_param_prog
	/bin/bash -c "(exec -a prog ./prog-a)" 2> test_null_param_prog_a
	LD_LIBRARY_PATH=`pwd` /bin/bash -c "(exec -a prog ./prog-so)" 2> test_null_param_prog_so
	./prog param > test_one_param_prog
	./prog-a param > test_one_param_prog_a
	LD_LIBRARY_PATH=`pwd` ./prog-so param > test_one_param_prog_so
	./prog first second > test_two_param_prog
	./prog-a first second > test_two_param_prog_a
	LD_LIBRARY_PATH=`pwd` ./prog-so first second > test_two_param_prog_so
	cmp test_null_param_prog test_null_param_prog_a
	cmp test_null_param_prog test_null_param_prog_so
	cmp test_one_param_prog test_one_param_prog_a
	cmp test_one_param_prog test_one_param_prog_so
	cmp test_two_param_prog test_two_param_prog_a
	cmp test_two_param_prog test_two_param_prog_so



prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o prog-a

prog-so: prog_shrd.o liboutput.so
	cc -L. prog_shrd.o -loutput -o prog-so	

README: prog
	./$< 2> $@



liboutput_static.a: const.o fun.o
	ar -rcs liboutput_static.a $^



liboutput.so: const_shrd.o fun_shrd.o
	cc -shared $^ -o liboutput.so

const_shrd.o: const.c
	cc -fPIC -c -o $@ $<

fun_shrd.o: fun.c
	cc -fPIC -c -o $@ $<

prog_shrd.o: prog.c
	cc -fPIC -c -o $@ $<



fun.o: outlib.h



clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)