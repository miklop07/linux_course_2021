TESTS = test_null test_pop test_trunc test_free test_push
check_PROGRAMS = $(TESTS)

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
