#ifndef ODBCLIB_CONFIG_HPP_INCLUDED
#define ODBCLIB_CONFIG_HPP_INCLUDED

//disable cl.exe warning about throw
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif
#include <stdexcept>

//#define DEBUG
#include "debug.hpp"
#undef DEBUG

#endif
