#ifndef ODBCLIB_DIAGINFOEVENTARGS_HPP_INCLUDED
#define ODBCLIB_DIAGINFOEVENTARGS_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

NS_BEGIN_1(odbclib)

class Handle;
class DiagInfo;
class DiagInfoEventArgs
{
public:
	DiagInfoEventArgs(Handle&,DiagInfo const&);
	DiagInfo const& getDiagInfo()const{return m_diagInfo;}
	Handle& getHandle()const{return m_handle;}
private:
	DiagInfo const& m_diagInfo;
	/*mutable*/ 
	Handle& m_handle;
};

NS_END_1

#endif
