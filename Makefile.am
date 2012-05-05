noinst_HEADERS = ./include/columnmetadata.hpp ./include/component.hpp ./include/config.hpp ./include/connection.hpp ./include/cursor.hpp ./include/debug.hpp ./include/decimal.hpp ./include/diaginfo.hpp ./include/diaginfoeventargs.hpp ./include/disposable.hpp ./include/disposeeventargs.hpp ./include/environment.hpp ./include/guid.hpp ./include/handle.hpp ./include/macros.hpp ./include/nullable.hpp ./include/odbclib.hpp ./include/resultset.hpp ./include/resultsetmetadata.hpp ./include/session.hpp ./include/statement.hpp ./include/transaction.hpp ./include/types.hpp ./include/utils/event/event.hpp ./include/utils/event/event.implement ./include/utils/event/event.template ./include/utils/event/eventlistener.hpp ./include/utils/event/eventlistener.implement ./include/utils/event/eventlistener.template ./include/utils/utils.hpp

lib_LTLIBRARIES = libodbclib.la
libodbclib_la_SOURCES = ./src/columnmetadata.cpp ./src/component.cpp ./src/connection.cpp ./src/cursor.cpp ./src/debug.cpp ./src/decimal.cpp ./src/diaginfo.cpp ./src/diaginfoeventargs.cpp ./src/environment.cpp ./src/guid.cpp ./src/handle.cpp ./src/nullable.cpp ./src/resultset.cpp ./src/resultsetmetadata.cpp ./src/session.cpp ./src/statement.cpp ./src/transaction.cpp ./src/types.cpp
libodbclib_la_LDFLAGS = -lodbc32 -no-undefined

noinst_PROGRAMS = odbclib
odbclib_SOURCES = ./src/main.cpp
odbclib_LDADD = libodbclib.la
