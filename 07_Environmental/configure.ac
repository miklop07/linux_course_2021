#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [0.00], [miklop07@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([Rhash is needed])])
AC_CHECK_LIB([readline], [readline], [], [])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])
AC_CHECK_HEADER([rhash.h])
AC_CHECK_HEADER([readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable readline library]),
    AC_DEFINE(HAVE_READLINE, [], [Replace getline to readline])
)
AC_ARG_WITH([readline],
        [AS_HELP_STRING([--without-readline],  [Disable readline library])], 
        [], [with_readline=yes]
)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
