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

libodbcxx_la_LDFLAGS = -lodbc

pkginclude_HEADERS = \
src/utils.hpp \
src/environment.hpp \
src/handle.hpp \
src/descriptor.hpp \
src/config.hpp \
src/diaginfo.hpp \
src/cursor.hpp \
src/session.hpp \
src/odbcxx.hpp \
src/statement.hpp \
src/rowset.hpp \
src/resultset.hpp \
src/transaction.hpp \
src/connection.hpp \
src/handle_object.hpp

noinst_PROGRAMS = test1
test1_SOURCES = test/main.cpp
test1_LDADD = libodbcxx.la
