#include "handle.hpp"
#include <ostream>
#include <iostream>

using namespace std;

namespace odbcxx {

	handle handle::null;

	handle::handle()
		:_M_handle(SQL_NULL_HANDLE), _M_type(0),
		_M_getter(0), _M_setter(0)
	{ }

	handle::handle(SQLHANDLE const h, SQLSMALLINT const t)
		:_M_handle(h), _M_type(t),
		_M_getter(0), _M_setter(0)
	{
		switch(t) {
			case SQL_HANDLE_ENV:
				_M_getter = &SQLGetEnvAttr;
				_M_setter = &SQLSetEnvAttr;
				break;
			case SQL_HANDLE_DBC:
				_M_getter = &SQLGetConnectAttr;
				_M_setter = &SQLSetConnectAttr;
				break;
			case SQL_HANDLE_STMT:
				_M_getter = &SQLGetStmtAttr;
				_M_setter = &SQLSetStmtAttr;
				break;
			default:break;
		}
	}

	SQLRETURN handle::get_attribute(SQLINTEGER attribute,
			SQLPOINTER value_ptr,
			SQLINTEGER buf_len,
			SQLINTEGER *out_len)
	{
		return check_error((*_M_getter)(_M_handle, attribute, value_ptr, buf_len, out_len));
	}

	SQLRETURN handle::get_attrb(SQLINTEGER attribute,
			std::string &v) {
		SQLRETURN retcode;
		char* buf = 0;
		SQLINTEGER buf_len = 0;
		SQLINTEGER required_len = 0;

		retcode = (*_M_getter)(_M_handle, attribute, reinterpret_cast<SQLPOINTER>(buf), buf_len, &required_len);
		if (!SQL_SUCCEEDED(retcode))
			return check_error(retcode);
		buf_len = required_len + (required_len % 2 ? 1 : 2);
		buf = new char[buf_len];
		retcode = check_error((*_M_getter)(_M_handle, attribute, reinterpret_cast<SQLPOINTER>(buf), buf_len, &required_len));
		if (SQL_SUCCEEDED(retcode))
			v.assign(buf);
		delete[] buf;
		return retcode;
	}

	SQLRETURN handle::set_attribute(SQLINTEGER attribute,
			SQLPOINTER value_ptr,
			SQLINTEGER buf_len)
	{
		return check_error((*_M_setter)(_M_handle, attribute, value_ptr, buf_len));
	}

	handle handle::alloc(handle::handle_type type) {
		SQLSMALLINT t = static_cast<SQLSMALLINT>(type);
		SQLHANDLE h;
		SQLRETURN ret = check_error(::SQLAllocHandle(t, _M_handle, &h));
		if(SQL_SUCCEEDED(ret))
			return handle(h, t);
		return handle::null;
	}

	SQLRETURN handle::close() {
		if(*this)
			return check_error(::SQLFreeHandle(_M_type, _M_handle));
		return SQL_SUCCESS;
	}

	SQLRETURN handle::diag(SQLSMALLINT rec_index, diaginfo &di) {
		return ::SQLGetDiagRec(_M_type,
				_M_handle,
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
			<< "{_M_handle = " << h._M_handle
			<< ", _M_type = " << h._M_type
			<< "(" << static_cast<handle::handle_type>(h._M_type) << ")"
			<< "}";
	}

}
