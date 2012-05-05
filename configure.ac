#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([odbclib],[1.0],[http://sourceforge.net/p/odbclib])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
LT_INIT

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lodbc32':
AC_CHECK_LIB([odbc32], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h malloc.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getcwd memset putenv realpath setenv strchr strerror strpbrk])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
