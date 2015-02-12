#ifndef ODBCLIB_CONFIG_HPP_INCLUDED
#define ODBCLIB_CONFIG_HPP_INCLUDED

#include "macros.hpp"

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

//disable cl.exe warning about throw
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif
#include <stdexcept>

#define DEBUG
#undef DEBUG
#include "debug.hpp"

#endif
