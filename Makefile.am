noinst_HEADERS = \
./include/disposeeventargs.hpp \
./include/macros.hpp \
./include/debug.hpp \
./include/resultsetmetadata.hpp \
./include/odbclib.hpp \
./include/decimal.hpp \
./include/cursor.hpp \
./include/columnmetadata.hpp \
./include/component.hpp \
./include/transaction.hpp \
./include/disposable.hpp \
./include/statement.hpp \
./include/handle.hpp \
./include/types.hpp \
./include/environment.hpp \
./include/utils/utils.hpp \
./include/utils/event/eventlistener.hpp \
./include/utils/event/event.hpp \
./include/guid.hpp \
./include/diaginfo.hpp \
./include/connection.hpp \
./include/diaginfoeventargs.hpp \
./include/session.hpp \
./include/nullable.hpp \
./include/resultset.hpp \
./include/config.hpp \
./include/utils/event/eventlistener.hdr.tcc \
./include/utils/event/event.hdr.tcc \
./include/utils/event/event.src.tcc \
./include/utils/event/eventlistener.src.tcc

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

libodbclib_la_LDFLAGS = -lodbc -no-undefined

noinst_PROGRAMS = test1
test1_SOURCES = ./test/main.cpp
test1_LDADD = libodbclib.la
