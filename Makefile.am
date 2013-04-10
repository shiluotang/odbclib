noinst_HEADERS = \
./src/debug.hpp \
./src/connection.hpp \
./src/session.hpp \
./src/statement.hpp \
./src/disposable.hpp \
./src/cursor.hpp \
./src/types.hpp \
./src/guid.hpp \
./src/columnmetadata.hpp \
./src/disposeeventargs.hpp \
./src/handle.hpp \
./src/diaginfo.hpp \
./src/config.hpp \
./src/resultsetmetadata.hpp \
./src/utils/utils.hpp \
./src/utils/event/eventlistener.hpp \
./src/utils/event/event.hpp \
./src/transaction.hpp \
./src/nullable.hpp \
./src/diaginfoeventargs.hpp \
./src/decimal.hpp \
./src/odbclib.hpp \
./src/macros.hpp \
./src/component.hpp \
./src/environment.hpp \
./src/resultset.hpp \
./src/utils/event/event.src.tcc \
./src/utils/event/event.hdr.tcc \
./src/utils/event/eventlistener.hdr.tcc \
./src/utils/event/eventlistener.src.tcc

lib_LTLIBRARIES = libodbclib.la
libodbclib_la_SOURCES = \
./src/types.cpp \
./src/statement.cpp \
./src/connection.cpp \
./src/session.cpp \
./src/nullable.cpp \
./src/guid.cpp \
./src/transaction.cpp \
./src/handle.cpp \
./src/columnmetadata.cpp \
./src/cursor.cpp \
./src/component.cpp \
./src/resultsetmetadata.cpp \
./src/resultset.cpp \
./src/diaginfoeventargs.cpp \
./src/diaginfo.cpp \
./src/decimal.cpp \
./src/environment.cpp \
./src/debug.cpp

libodbclib_la_LDFLAGS = -lodbc32 -no-undefined

noinst_PROGRAMS = test1
test1_SOURCES = ./test/main.cpp
test1_LDADD = libodbclib.la
