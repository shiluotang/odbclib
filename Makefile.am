ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Wall
AM_CXXFLAGS = -std=c++11

lib_LTLIBRARIES = libodbcxx.la
libodbcxx_la_SOURCES = \
src/cursor.cpp \
src/transaction.cpp \
src/handle_object.cpp \
src/handle.cpp \
src/rowset.cpp \
src/descriptor.cpp \
src/session.cpp \
src/environment.cpp \
src/statement.cpp \
src/connection.cpp \
src/diaginfo.cpp \
src/resultset.cpp \
src/odbc_error.cpp \
src/buffer.cpp

if USE_ODBC32
ODBC_LDFLAGS = -lodbc32
else
ODBC_LDFLAGS = -lodbc -lpthread
endif

libodbcxx_la_LDFLAGS = -no-undefined $(ODBC_LDFLAGS)
 
noinst_PROGRAMS = test1
test1_SOURCES = test/main.cpp
test1_LDADD = libodbcxx.la

SUBDIRS = src

include $(top_srcdir)/doxygen-automake.am
EXTRA_DIST = Doxyfile
