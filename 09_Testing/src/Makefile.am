CFLAGS = -Wall

if COND_GCOV
CFLAGS += -fprofile-arcs -ftest-coverage -O0 -g
else 
CFLAGS += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la
libbuf_la_SOURCES = libbuf.c
libbuf_la_LDFLAGS = -version-info 0:0:0

bin_PROGRAMS = buf
buf_SOURCES = buf.c
buf_LDADD = libbuf.la

gitclean: maintainer-clean
	git clean -fd

gcov:
	gcov -o .libs libbuf -t -k -b
