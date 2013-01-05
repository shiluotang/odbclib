#include "connection.hpp"
#include "environment.hpp"
#include "session.hpp"

using namespace std;

namespace odbcxx {

	connection::connection() {}

	session& connection::connect(session& s,
			char const* server_name, 
			char const *user_name,
			char const *authentication) {
		SQLRETURN ret = m_handle.check_error(SQLConnect(m_handle.raw(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(server_name)),
			SQL_NTS,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(server_name)),
			SQL_NTS,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(server_name)),
			SQL_NTS));
		if(SQL_SUCCEEDED(ret))
			s.m_conn_ptr = this;
		return s;
	}

	session& connection::driver_connect(session &s,
			char const * in_connstr,
			SQLUSMALLINT driver_completion,
			SQLHWND hwnd) {
		SQLSMALLINT len;
		SQLRETURN ret = m_handle.check_error(SQLDriverConnect(
			m_handle.raw(),
			hwnd,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(in_connstr)),
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
			char const* in_connstr) 
	{
		SQLSMALLINT len;
		SQLRETURN ret = m_handle.check_error(SQLBrowseConnect(
			m_handle.raw(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(in_connstr)),
			SQL_NTS,
			&s.m_buf[0],
			countof(s.m_buf),
			&len));
		s.m_buf[countof(s.m_buf) - 1] = 0;
		if(SQL_SUCCEEDED(ret))
			s.m_conn_ptr = this;
		return s;
	}
}
