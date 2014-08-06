#include "connection.hpp"
#include "environment.hpp"
#include "session.hpp"

#include <utility>

using namespace std;

namespace odbcxx {

	connection::connection() {}

	session& connection::connect(session& s,
			string const& server_name,
			string const &user_name,
			string const &authentication) {
		SQLRETURN ret = m_handle.check_error(SQLConnect(m_handle.raw(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(server_name.c_str())),
			SQL_NTS,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(user_name.c_str())),
			SQL_NTS,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(authentication.c_str())),
			SQL_NTS));
		if(SQL_SUCCEEDED(ret))
			s.m_conn_ptr = this;
		return s;
	}

	session& connection::driver_connect(session &s,
			string const &in_connstr,
			SQLUSMALLINT driver_completion,
			SQLHWND hwnd) {
		SQLSMALLINT len;
		SQLRETURN ret = m_handle.check_error(SQLDriverConnect(
			m_handle.raw(),
			hwnd,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(in_connstr.c_str())),
			SQL_NTS,
			&s.m_buf[0],
			countof(s.m_buf),
			&len,
			driver_completion));
		s.m_buf[countof(s.m_buf) - 1] = 0;
		if(SQL_SUCCEEDED(ret))
			s.m_conn_ptr = this;
		return s;
	}

	session& connection::browse_connect(session &s,
			string const& in_connstr)
	{
		SQLSMALLINT len;
		SQLRETURN ret = m_handle.check_error(SQLBrowseConnect(
			m_handle.raw(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(in_connstr.c_str())),
			SQL_NTS,
			&s.m_buf[0],
			countof(s.m_buf),
			&len));
		s.m_buf[countof(s.m_buf) - 1] = 0;
		if(SQL_SUCCEEDED(ret))
			s.m_conn_ptr = this;
		return s;
	}

	SQLRETURN connection::disconnect() {
		if(*this)
			return m_handle.check_error(SQLDisconnect(m_handle.raw()));
		return SQL_SUCCESS;
	}

	SQLRETURN connection::commit() {
		if(*this)
			return m_handle.check_error(::SQLEndTran(
					m_handle.type(),
					m_handle.raw(),
					SQL_COMMIT));
		return SQL_SUCCESS;
	}

	SQLRETURN connection::rollback() {
		if(*this)
			return m_handle.check_error(::SQLEndTran(
					m_handle.type(),
					m_handle.raw(),
					SQL_ROLLBACK));
		return SQL_SUCCESS;
	}

	connection& connection::current_catalog(string const &catalog) {
		if(*this)
			m_handle.set_attrb(SQL_ATTR_CURRENT_CATALOG, catalog);
		return *this;
	}
	string const connection::current_catalog() {
		string catalog;
		m_handle.get_attrb(SQL_ATTR_CURRENT_CATALOG, catalog);
		return catalog;
	}

	string const connection::native_sql(string const &sql) {
		string native;

		SQLRETURN retcode;
		char *buf = 0;
		SQLINTEGER buf_len = 0;
		SQLINTEGER out_len = 0;

		retcode = ::SQLNativeSql(m_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())), SQL_NTS,
				reinterpret_cast<SQLCHAR*>(buf), buf_len,
				&out_len);
		if (!SQL_SUCCEEDED(retcode)) {
			m_handle.check_error(retcode);
			return std::move(native);
		}
		buf_len = out_len + (out_len % 2 ? 1 : 2);
		buf = new char[buf_len];
		retcode = SQLNativeSql(m_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())), SQL_NTS,
				reinterpret_cast<SQLCHAR*>(buf), buf_len,
				&out_len);
		m_handle.check_error(retcode);
		if (SQL_SUCCEEDED(retcode))
			native.assign(buf);
		delete[] buf;
		return native;
	}

	SQLRETURN connection::get_info(SQLUSMALLINT info_type,
			SQLPOINTER buf,
			SQLSMALLINT buf_len,
			SQLSMALLINT *required_len) {
		return m_handle.check_error(::SQLGetInfo(
					m_handle.raw(),
					info_type,
					buf,
					buf_len,
					required_len));
	}

	SQLRETURN connection::get_info(SQLUSMALLINT info_type, string &v) {
		SQLRETURN retcode;
		char *buf = 0;
		SQLSMALLINT buf_len = 0;
		SQLSMALLINT required_len = 0;

		retcode = ::SQLGetInfo(m_handle.raw(), info_type,
				reinterpret_cast<SQLPOINTER>(buf), buf_len,
				&required_len);
		if (!SQL_SUCCEEDED(retcode))
			return m_handle.check_error(retcode);
		buf_len = required_len + (required_len % 2 ? 1 : 2);
		buf = new char[buf_len];
		retcode = m_handle.check_error(::SQLGetInfo(m_handle.raw(), info_type,
					reinterpret_cast<SQLPOINTER>(buf), buf_len,
					&required_len));
		if (SQL_SUCCEEDED(retcode))
			v.assign(buf);
		delete[] buf;
		return retcode;
	}
}
