#ifndef ODBCXX_MACROS_HPP_INCLUDED
#define ODBCXX_MACROS_HPP_INCLUDED

#define OS_UNIX 0
#define OS_LINUX 1
#define OS_WINDOWS 2

#undef OS_TYPE

#if defined (_WIN32) && defined(_MINGW32_) || defined(_WIN32) && defined(_MINGW64_) || defined(_WIN32) && defined(_MSC_VER)
#define OS_TYPE OS_WINDOWS
#else
#define OS_TYPE OS_LINUX
#endif

#if OS_TYPE == OS_WINDOWS
#include <windows.h>
#include <odbcinst.h>
#else
#include <odbcinst.h>
#endif

#include <sql.h>
#include <sqlucode.h>
#include <sqlext.h>

#include "utils.hpp"

#endif //ODBCXX_MACROS_HPP_INCLUDED
