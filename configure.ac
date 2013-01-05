#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([odbcxx], [1.0], [Samuel Winchester])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
LT_INIT
AC_CONFIG_SRCDIR([src/config.hpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lodbc':
AC_CHECK_LIB([odbc], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
