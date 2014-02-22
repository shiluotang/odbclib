#ifndef ODBCXX_MACROS_HPP_INCLUDED
#define ODBCXX_MACROS_HPP_INCLUDED

#if defined(_WIN32)
#   include <windows.h>
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#   include <windows.h>
#elif defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
#   include <windows.h>
#endif

#include <odbcinst.h>
#include <sql.h>
#include <sqlucode.h>
#include <sqlext.h>

#include "utils.hpp"

#endif //ODBCXX_MACROS_HPP_INCLUDED
