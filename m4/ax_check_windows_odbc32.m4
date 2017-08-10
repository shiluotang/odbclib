AC_DEFUN([AX_CHECK_WINDOWS_ODBC32], [
    AC_MSG_CHECKING([whether -lodbc32 contains SQLDisconnect])
    OLD_LIBS=$LIBS
    LIBS="-lodbc32 $LIBS"
    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
            [
                #include <windows.h>
                #include <sql.h>
                #include <sqlext.h>
                #include <sqltypes.h>
                #include <sqlucode.h>
            ],
            [
                return &SQLDisconnect != NULL;
            ]
        )],
        [HAVE_ODBC32=yes],
        [HAVE_ODBC32=no]
    )
    AC_MSG_RESULT([$HAVE_ODBC32])
    LIBS=$OLD_LIBS
])
