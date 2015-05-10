#include "handle.hpp"
#include "odbc_error.hpp"
#include "buffer.hpp"
#include <ostream>
#include <iostream>

using namespace std;

#define DEFINE_SIMPLE_GETTER(TYPE) \
	handle const& handle::get_attrb(SQLINTEGER attribute, SQL##TYPE &value) const { \
		throw_error((*_M_getter)(_M_handle, \
				attribute, \
				reinterpret_cast<SQLPOINTER>(&value), \
				SQL_IS_##TYPE, \
				0)); \
		return *this; \
	}

#define DEFINE_SIMPLE_SETTER(TYPE) \
	handle& handle::set_attrb(SQLINTEGER attribute, SQL##TYPE value) { \
		throw_error((*_M_setter)(_M_handle, \
				attribute, \
				reinterpret_cast<SQLPOINTER>(value), \
				SQL_IS_##TYPE)); \
		return *this; \
	}

namespace {
	enum handle_type {
		ENV = SQL_HANDLE_ENV,
		DBC = SQL_HANDLE_DBC,
		STMT = SQL_HANDLE_STMT,
		DESC = SQL_HANDLE_DESC
	};

	ostream& operator << (ostream &os, handle_type type) {
		switch(type) {
			case ENV: return os << "SQL_HANDLE_ENV";
			case DBC: return os << "SQL_HANDLE_DBC";
			case STMT: return os << "SQL_HANDLE_STMT";
			case DESC: return os << "SQL_HANDLE_DESC";
			default: return os << "<UNKNOWN>";
		}
	}
}

namespace odbcxx {

	handle const handle::null;

	handle::handle(SQLHANDLE h, SQLSMALLINT type)
		:_M_handle(h), _M_type(type),
		_M_getter(0), _M_setter(0)
	{
		switch(type) {
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

	handle handle::alloc(SQLSMALLINT type) const {
		SQLHANDLE h;
		throw_error(::SQLAllocHandle(type, _M_handle, &h));
		return handle(h, type);
	}

	void handle::close() {
		if (*this) {
			throw_error(::SQLFreeHandle(_M_type, _M_handle));
			_M_handle = SQL_NULL_HANDLE;
		}
	}

	DEFINE_SIMPLE_GETTER(SMALLINT)
	DEFINE_SIMPLE_GETTER(USMALLINT)
	DEFINE_SIMPLE_GETTER(INTEGER)
	DEFINE_SIMPLE_GETTER(UINTEGER)
	DEFINE_SIMPLE_GETTER(POINTER)

	handle const& handle::get_attrb(SQLINTEGER attribute, string &value) const {
		SQLINTEGER chars = 0;
		buffer buf(0);

		throw_error((*_M_getter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(buf.addr()), 0,
				&chars));
		buf.resize(chars + 1);
		throw_error((*_M_getter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(buf.addr()), buf.size(),
				&chars));
		value.assign(buf.addr());
		return *this;
	}
	handle const& handle::get_attrb(SQLINTEGER attribute, wstring &value) const {
		SQLINTEGER chars = 0;
		buffer buf(0);

		throw_error((*_M_getter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(buf.addr()), 0,
				&chars));
		buf.resize(chars + 2);
		throw_error((*_M_getter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(buf.addr()), buf.size(),
				&chars));
		value.assign(reinterpret_cast<wchar_t*>(buf.addr()));
		return *this;
	}

	DEFINE_SIMPLE_SETTER(SMALLINT)
	DEFINE_SIMPLE_SETTER(USMALLINT)
	DEFINE_SIMPLE_SETTER(INTEGER)
	DEFINE_SIMPLE_SETTER(UINTEGER)
	DEFINE_SIMPLE_SETTER(POINTER)

	handle& handle::set_attrb(SQLINTEGER attribute, string const &value) {
		throw_error((*_M_setter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(const_cast<char*>(value.c_str())),
				SQL_NTS));
		return *this;
	}
	handle& handle::set_attrb(SQLINTEGER attribute, wstring const &value) {
		throw_error((*_M_setter)(_M_handle,
				attribute,
				reinterpret_cast<SQLPOINTER>(const_cast<wchar_t*>(value.c_str())),
				SQL_NTS));
		return *this;
	}

	/**
	 * \brief There're many things you SHOULD know!
	 *
	 * SQLGetDiagRec does not post diagnostic records for itself. It uses the
	 * following return values to report the outcome of its own execution:
	 *
	 * 1.SQL_SUCCESS: The function successfully returned diagnostic information. 
	 *
	 * 2.SQL_SUCCESS_WITH_INFO: The <code>*MessageText</code> buffer was too
	 * small to hold the requested diagnostic message. No diagnostic records
	 * were generated. To determine that a truncation occurred, the application
	 * must compare <code>BufferLength</code> to the actual number of bytes
	 * available, which is written to <code>*StringLengthPtr</code>.
	 *
	 * 3.SQL_INVALID_HANDLE: The handle indicated by <code>HandleType</code> and
	 * <code>Handle</code> was not a valid handle. 
	 *
	 * 4.SQL_ERROR: One of the following occurred:
	 * 		<code>RecNumber</code> was negative or 0.
	 * 		<code>BufferLength</code> was less than zero. 
	 * 		When using asynchronous notification, the asynchronous operation on
	 * 		the handle was not complete. 
	 *
	 * 5.SQL_NO_DATA: <code>RecNumber</code> was greater than the number of
	 * diagnostic records that existed for the handle specified in
	 * <code>Handle</code>. The function also returns SQL_NO_DATA for any
	 * positive <code>RecNumber</code> if there are no diagnostic records for
	 * <code>Handle</code>.
	 *
	 *
	 * All these above means even if there're something wrong with the
	 * invokation of SQLGetDiagRec we can't get that message through another
	 * invokation of SQLGetDiagRec. What we can get is just the SQLRETURN
	 * values. That's what all we got.
	 */
	SQLRETURN handle::diag(SQLSMALLINT rec_index, diaginfo &di) const {
		SQLRETURN retcode;
		buffer buf(0);
		SQLSMALLINT chars = 0;

		retcode = ::SQLGetDiagRec(_M_type,
				_M_handle,
				rec_index,
				&di._M_state[0],
				&di._M_native_error_code,
				NULL, 0,
				&chars);
		if (!SQL_SUCCEEDED(retcode)) {
			if (retcode == SQL_INVALID_HANDLE)
				_M_handle = SQL_NULL_HANDLE;
			return retcode;
		}
        buf.resize(chars + 1);
		retcode = ::SQLGetDiagRec(_M_type,
				_M_handle,
				rec_index,
				&di._M_state[0],
				&di._M_native_error_code,
				reinterpret_cast<SQLCHAR*>(buf.addr()), buf.size(),
				&chars);
		if (SQL_SUCCEEDED(retcode))
			di._M_message.assign(buf.addr());
		if (retcode == SQL_INVALID_HANDLE)
			_M_handle = SQL_NULL_HANDLE;
		return retcode;
	}

	handle const& handle::log_error(SQLRETURN retcode) const {
		if (!(*this))
			return *this;
		if(retcode == SQL_INVALID_HANDLE) {
			_M_handle = SQL_NULL_HANDLE;
			return *this;
		}
		if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
			SQLRETURN rc;
			SQLSMALLINT index = 0;
			diaginfo info;
			while (SQL_SUCCEEDED(rc = diag(++index, info)))
				clog << "[diagnostics]" << info << endl;
			if(rc == SQL_INVALID_HANDLE)
				_M_handle = SQL_NULL_HANDLE;
			else if (rc == SQL_ERROR)
				clog << "[diagnostics] Asynchronous operation on this handle "
					<< "is not complete."
					<< endl;
		} else if (retcode == SQL_STILL_EXECUTING)
			clog << "[diagnostics] SQLCompleteAsync has not been called to "
				<< "complete the previous asynchronous operation on this handle."
				<< endl;
		else if (retcode == SQL_NO_DATA) {
			clog << "[diagnostics] Specified attribute does not have a default "
				<< "and has not been set."
				<< endl;
		}
		return *this;
	}
	handle const& handle::ignore_error(SQLRETURN retcode) const {
		if (!(*this))
			return *this;
		if(retcode == SQL_INVALID_HANDLE) {
			_M_handle = SQL_NULL_HANDLE;
			return *this;
		}
		if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
			SQLRETURN rc;
			SQLSMALLINT index = 0;
			diaginfo info;
			while (SQL_SUCCEEDED(rc = diag(++index, info)));
			if(rc == SQL_INVALID_HANDLE)
				_M_handle = SQL_NULL_HANDLE;
		}
		return *this;
	}
	handle const& handle::throw_error(SQLRETURN retcode) const {
		if (!(*this))
			return *this;
		if(retcode == SQL_INVALID_HANDLE) {
			_M_handle = SQL_NULL_HANDLE;
			throw odbc_error("Invalid handle.");
		}

		if (retcode == SQL_ERROR) {
			SQLRETURN rc;
			SQLSMALLINT index = 0;
			diaginfo info;
			stringstream ss;
			while (SQL_SUCCEEDED(rc = diag(++index, info)))
				ss << info << endl;
			if(rc == SQL_INVALID_HANDLE) {
				_M_handle = SQL_NULL_HANDLE;
				if (index == 1)
					throw odbc_error("Invalid handle.");
				throw odbc_error(ss.str());
			} else if (rc == SQL_ERROR) {
				if (index == 1)
					throw odbc_error("Asynchronous operation on "
							"this handle is not complete.");
				throw odbc_error(ss.str());
			} else if (index > 1)
				throw odbc_error(ss.str());
		} else if (retcode == SQL_STILL_EXECUTING)
			throw odbc_error("SQLCompleteAsync has not been called to "
					"complete the previous asynchronous operation "
					"on this handle.");
		else if (retcode == SQL_NO_DATA)
			throw odbc_error("Specified attribute does not have a default "
					"and has not been set.");
		return *this;
	}

	ostream& operator << (ostream& os, handle const& h) {
		return os << "handle@" << &h
			<< "{_M_handle = " << h._M_handle
			<< ", _M_type = " << h._M_type
			<< "(" << static_cast<handle_type>(h._M_type) << ")"
			<< "}";
	}

}
