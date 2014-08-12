#include "handle.hpp"
#include <ostream>
#include <iostream>

using namespace std;

#define DEFINE_SIMPLE_GETTER(TYPE) \
	SQLRETURN handle::get_attrb(SQLINTEGER attribute, SQL##TYPE &value) { \
		return check_error((*_M_getter)(_M_handle, attribute, reinterpret_cast<SQLPOINTER>(&value),SQL_IS_##TYPE, 0)); \
	}

#define DEFINE_SIMPLE_SETTER(TYPE) \
	SQLRETURN handle::set_attrb(SQLINTEGER attribute, SQL##TYPE const &value) { \
		return check_error((*_M_setter)(_M_handle, attribute, reinterpret_cast<SQLPOINTER>(value), SQL_IS_##TYPE)); \
	}

namespace {
}

namespace odbcxx {

	handle handle::null;

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

	DEFINE_SIMPLE_GETTER(SMALLINT)
	DEFINE_SIMPLE_GETTER(USMALLINT)
	DEFINE_SIMPLE_GETTER(INTEGER)
	DEFINE_SIMPLE_GETTER(UINTEGER)

	SQLRETURN handle::get_attrb(SQLINTEGER attribute, string &value) {
		SQLRETURN retcode;
		char *buf = 0;
		SQLINTEGER chars;

		retcode = (*_M_getter)(_M_handle,
				attribute,
				NULL, 0,
				&chars);
		if (!SQL_SUCCEEDED(retcode))
			return check_error(retcode);
		buf = new char[chars + 1];
		retcode = (*_M_getter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(buf), chars + 1,
				&chars);
		return check_error(retcode);
	}
	SQLRETURN handle::get_attrb(SQLINTEGER attribute, wstring &value) {
		SQLRETURN retcode;
		wchar_t *buf = 0;
		SQLINTEGER chars;

		retcode = (*_M_getter)(_M_handle,
				attribute,
				NULL, 0,
				&chars);
		if (!SQL_SUCCEEDED(retcode))
			return check_error(retcode);
		buf = new wchar_t[(chars >> 1) + 1];
		retcode = (*_M_getter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(buf), (chars >> 1) + 1,
				&chars);
		return check_error(retcode);
	}

	DEFINE_SIMPLE_SETTER(SMALLINT)
	DEFINE_SIMPLE_SETTER(USMALLINT)
	DEFINE_SIMPLE_SETTER(INTEGER)
	DEFINE_SIMPLE_SETTER(UINTEGER)

	SQLRETURN handle::set_attrb(SQLINTEGER attribute, SQLPOINTER value) {
		return check_error((*_M_setter)(_M_handle, attribute, value, SQL_IS_POINTER));
	}
	SQLRETURN handle::set_attrb(SQLINTEGER attribute, string const &value) {
		return check_error((*_M_setter)(_M_handle,
					attribute,
					reinterpret_cast<SQLPOINTER>(const_cast<char*>(value.c_str())),
					SQL_NTS));
	}
	SQLRETURN handle::set_attrb(SQLINTEGER attribute, wstring const &value) {
		return check_error((*_M_setter)(_M_handle,
					attribute,
					reinterpret_cast<SQLPOINTER>(const_cast<wchar_t*>(value.c_str())),
					SQL_NTS));
	}

	SQLRETURN handle::diag(SQLSMALLINT rec_index, diaginfo &di) {
		SQLRETURN retcode;
		char *buf = 0;
		SQLSMALLINT chars = 0;

		retcode = ::SQLGetDiagRec(_M_type,
				_M_handle,
				rec_index,
				&di._M_state[0],
				&di._M_native_error_code,
				NULL, 0,
				&chars);
		if (!SQL_SUCCEEDED(retcode))
			return retcode;

		buf = new char[chars + 1];
		retcode = ::SQLGetDiagRec(_M_type,
				_M_handle,
				rec_index,
				&di._M_state[0],
				&di._M_native_error_code,
				reinterpret_cast<SQLCHAR*>(buf), chars + 1,
				&chars);
		if (SQL_SUCCEEDED(retcode))
			di._M_message.assign(buf);
		delete[] buf;
		return retcode;
	}

	SQLRETURN handle::check_error(SQLRETURN retcode) {
		if(retcode == SQL_SUCCESS)
			return retcode;
		if(retcode == SQL_INVALID_HANDLE) {
			*this = handle::null;
			return retcode;
		}
		SQLRETURN ret;
		SQLSMALLINT index = 0;
		diaginfo info;
		do {
			ret = diag(++index, info);
			if (!SQL_SUCCEEDED(ret))
				break;
			clog << "[diagnostics]" << info << endl;
		} while(true);
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
