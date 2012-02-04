#include "../include/diaginfoeventargs.hpp"

NS_BEGIN_1(odbclib)

DiagInfoEventArgs::DiagInfoEventArgs(Handle& handle,
		DiagInfo const& diag)
	:m_diagInfo(diag),
	m_handle(handle)
{}

NS_END_1
