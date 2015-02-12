ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -Wall
AM_CXXFLAGS = -std=c++11

lib_LTLIBRARIES = libodbclib.la
libodbclib_la_SOURCES = \
./src/columnmetadata.cpp \
./src/component.cpp \
./src/connection.cpp \
./src/cursor.cpp \
./src/debug.cpp \
./src/decimal.cpp \
./src/diaginfo.cpp \
./src/diaginfoeventargs.cpp \
./src/environment.cpp \
./src/guid.cpp \
./src/handle.cpp \
./src/nullable.cpp \
./src/resultset.cpp \
./src/resultsetmetadata.cpp \
./src/session.cpp \
./src/statement.cpp \
./src/transaction.cpp \
./src/types.cpp

if USE_ODBC32
ODBC_LDFLAGS = -lodbc32
else
ODBC_LDFLAGS = -lodbc -lpthread
endif

libodbclib_la_LDFLAGS = -no-undefined $(ODBC_LDFLAGS)
 
noinst_PROGRAMS = test1
test1_SOURCES = test/main.cpp
test1_LDADD = libodbclib.la

SUBDIRS = src

include $(top_srcdir)/doxygen-automake.am
EXTRA_DIST = Doxyfile
