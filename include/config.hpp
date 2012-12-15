#ifndef ODBCLIB_CONFIG_HPP_INCLUDED
#define ODBCLIB_CONFIG_HPP_INCLUDED

#if OS_TYPE == OS_WINDOWS
#include <windows.h>
#include <odbcinst.h>
#elif OS_TYPE == OS_LINUX || OS_TYPE == OS_UNIX
#include <odbcinst.h>
#elif OS_TYPE == OS_MAC
#error mac is not supported yet!
#endif

//disable cl.exe warning about throw
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif
#include <stdexcept>

#define DEBUG
#undef DEBUG
#include "debug.hpp"

#endif
