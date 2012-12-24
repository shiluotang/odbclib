#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([odbclib],[1.0],[http://sourceforge.net/p/odbclib])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
LT_INIT

AC_CONFIG_SRCDIR([include/odbclib.hpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lodbc32':
AC_CHECK_LIB([odbc32], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
