ACLOCAL_AMFLAGS = -I m4

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
src/resultset.cpp

libodbcxx_la_LDFLAGS = -lodbc32 -no-undefined

noinst_PROGRAMS = test1
test1_SOURCES = test/main.cpp
test1_LDADD = libodbcxx.la
test1_LDFLAGS = -all-static

SUBDIRS = src

include $(top_srcdir)/doxygen-automake.am
EXTRA_DIST = Doxyfile
