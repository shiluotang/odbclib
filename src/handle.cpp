#include "handle.hpp"
#include <ostream>
#include <iostream>

using namespace std;

namespace odbcxx {

	handle handle::null;

	handle::handle() 
		:m_handle(SQL_NULL_HANDLE), m_type(0),
		m_getter(0), m_setter(0) 
	{ }

	handle::handle(SQLHANDLE const h, SQLSMALLINT const t)
		:m_handle(h), m_type(t),
		m_getter(0), m_setter(0)
	{
		switch(t) {
			case SQL_HANDLE_ENV:
				m_getter = &SQLGetEnvAttr;
				m_setter = &SQLSetEnvAttr;
				break;
			case SQL_HANDLE_DBC:
				m_getter = &SQLGetConnectAttr;
				m_setter = &SQLSetConnectAttr;
				break;
			case SQL_HANDLE_STMT:
				m_getter = &SQLGetStmtAttr;
				m_setter = &SQLSetStmtAttr;
				break;
			default:break;
		}
	}

	SQLRETURN handle::get_attribute(SQLINTEGER attribute, 
			SQLPOINTER value_ptr, 
			SQLINTEGER buf_len, 
			SQLINTEGER *out_len)
	{  return check_error((*m_getter)(m_handle, attribute, value_ptr, buf_len, out_len)); }
	
	SQLRETURN handle::set_attribute(SQLINTEGER attribute,
			SQLPOINTER value_ptr,
			SQLINTEGER buf_len)
	{ return check_error((*m_setter)(m_handle, attribute, value_ptr, buf_len)); }

	handle handle::alloc(handle::handle_type type) {
		SQLSMALLINT t = static_cast<SQLSMALLINT>(type);
		SQLHANDLE h;
		SQLRETURN ret = check_error(::SQLAllocHandle(t, m_handle, &h));
		if(SQL_SUCCEEDED(ret))
			return handle(h, t);
		return handle::null;
	}

	SQLRETURN handle::close() { 
		if(*this)
			return check_error(::SQLFreeHandle(m_type, m_handle)); 
		return SQL_SUCCESS;
	}

	SQLRETURN handle::diag(SQLSMALLINT rec_index, diaginfo &di) {
		return ::SQLGetDiagRec(m_type,
				m_handle,
				rec_index,
				&di.m_state[0],
				&di.m_nec,
				&di.m_msg[0],
				sizeof(di.m_msg) / sizeof(di.m_msg[0]),
				0);
	}

	SQLRETURN handle::check_error(SQLRETURN retcode) {
		if(retcode == SQL_SUCCESS)
			return retcode;
		if(retcode == SQL_INVALID_HANDLE) {
			*this = handle::null;
			return retcode;
		}
		SQLSMALLINT index = 0;
		diaginfo info;
		while(diag(++index, info) == SQL_SUCCESS)
			clog << "[diagnostics]" << info << endl;
		return retcode;
	}

	ostream& operator << (ostream& os, handle::handle_type t) {
		os << "handle_type::";
		switch(t) {
			case handle::ENV: return os << "ENV";
			case handle::DBC: return os << "DBC";
			case handle::STMT: return os << "STMT";
			case handle::DESC: return os << "DESC";
			default: return os << "<UNKNOWN>";
		}
	}

	ostream& operator << (ostream& os, handle const& h) {
		return os << "handle@" << &h 
			<< "{m_handle = " << h.m_handle
			<< ", m_type = " << h.m_type 
			<< "(" << static_cast<handle::handle_type>(h.m_type) << ")"
			<< "}";
	}

}
