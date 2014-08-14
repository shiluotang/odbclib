#include "connection.hpp"
#include "environment.hpp"
#include "session.hpp"
#include "buffer.hpp"

#include <utility>

using namespace std;

#define DEFINE_SIMPLE_GETTER(TYPE) \
	connection& connection::get_info(SQLUSMALLINT info_type, SQL##TYPE &value) { \
		_M_handle.throw_error( \
				SQLGetInfo( \
					_M_handle.raw(), \
					info_type, \
					reinterpret_cast<SQLPOINTER>(&value), \
					SQL_IS_##TYPE, \
					0)); \
		return *this; \
	}

namespace odbcxx {

	connection::connection() {}

	session& connection::connect(session& s,
			string const& server_name,
			string const &user_name,
			string const &authentication) {
		_M_handle.throw_error(SQLConnect(_M_handle.raw(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(server_name.c_str())),
			SQL_NTS,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(user_name.c_str())),
			SQL_NTS,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(authentication.c_str())),
			SQL_NTS));
		s._M_conn_ptr = this;
		return s;
	}

	session& connection::driver_connect(session &s,
			string const &in_connstr,
			SQLUSMALLINT driver_completion,
			SQLHWND hwnd) {
		SQLSMALLINT len = 0;
		_M_handle.throw_error(SQLDriverConnect(
			_M_handle.raw(),
			hwnd,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(in_connstr.c_str())),
			SQL_NTS,
			&s.m_buf[0],
			countof(s.m_buf),
			&len,
			driver_completion));
		s.m_buf[countof(s.m_buf) - 1] = 0;
		s._M_conn_ptr = this;
		return s;
	}

	session& connection::browse_connect(session &s,
			string const& in_connstr) {
		SQLSMALLINT len = 0;
		_M_handle.throw_error(SQLBrowseConnect(
			_M_handle.raw(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(in_connstr.c_str())),
			SQL_NTS,
			&s.m_buf[0],
			countof(s.m_buf),
			&len));
		s.m_buf[countof(s.m_buf) - 1] = 0;
		s._M_conn_ptr = this;
		return s;
	}

	connection& connection::current_catalog(string const &catalog) {
		if(*this)
			_M_handle.set_attrb(SQL_ATTR_CURRENT_CATALOG, catalog);
		return *this;
	}
	string const connection::current_catalog() {
		string catalog;
		_M_handle.get_attrb(SQL_ATTR_CURRENT_CATALOG, catalog);
		return catalog;
	}

	bool connection::auto_commit() {
		SQLUINTEGER status;
		_M_handle.get_attrb(SQL_ATTR_AUTOCOMMIT, status);
		return status == SQL_AUTOCOMMIT_ON;
	}
	connection& connection::auto_commit(bool flag) {
		SQLUINTEGER status = flag ? SQL_AUTOCOMMIT_ON : SQL_AUTOCOMMIT_OFF;
		_M_handle.set_attrb(SQL_ATTR_AUTOCOMMIT, status);
		return *this;
	}

	string const connection::native_sql(string const &sql) {
		buffer buf(0);
		SQLINTEGER out_len = 0;
		_M_handle.throw_error(SQLNativeSql(_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())), SQL_NTS,
				reinterpret_cast<SQLCHAR*>(buf.addr()), buf.size(),
				&out_len));
		string native;
		buf.resize(out_len + 1);
		_M_handle.throw_error(SQLNativeSql(_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())), SQL_NTS,
				reinterpret_cast<SQLCHAR*>(buf.addr()), buf.size(),
				&out_len));
		native.assign(buf.addr());
		return native;
	}

	connection& connection::disconnect() {
		if(*this)
			_M_handle.throw_error(SQLDisconnect(_M_handle.raw()));
		return *this;
	}

	connection& connection::commit() {
		if(*this)
			_M_handle.throw_error(::SQLEndTran(
						_M_handle.type(),
						_M_handle.raw(),
						SQL_COMMIT));
		return *this;
	}

	connection& connection::rollback() {
		if(*this)
			_M_handle.throw_error(::SQLEndTran(
						_M_handle.type(),
						_M_handle.raw(),
						SQL_ROLLBACK));
		return *this;
	}

	DEFINE_SIMPLE_GETTER(SMALLINT)
	DEFINE_SIMPLE_GETTER(USMALLINT)
	DEFINE_SIMPLE_GETTER(INTEGER)
	DEFINE_SIMPLE_GETTER(UINTEGER)

	connection& connection::get_info(SQLUSMALLINT info_type, string &v) {
		buffer buf(0);
		SQLSMALLINT required_len = 0;
		_M_handle.throw_error(::SQLGetInfo(_M_handle.raw(), info_type,
				reinterpret_cast<SQLPOINTER>(buf.addr()), buf.size(),
				&required_len));
		buf.resize(required_len + 1);
		_M_handle.throw_error(::SQLGetInfo(_M_handle.raw(), info_type,
					reinterpret_cast<SQLPOINTER>(buf.addr()), buf.size(),
					&required_len));
		v.assign(buf.addr());
		return *this;
	}
}
