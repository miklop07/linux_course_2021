#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([regexp_task], [0.00], [miklop07@gmail.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([esub.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([regcomp])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
