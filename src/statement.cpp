#include "statement.hpp"
#include "session.hpp"
#include "cursor.hpp"
#include <string>

using namespace std;

namespace odbcxx {

	statement& statement::prepare(string const &cmd) {
		if(*this)
			this->m_handle.check_error(::SQLPrepare(this->m_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd.c_str())),
				SQL_NTS));
		return *this;
	}

	cursor& statement::execute(cursor &c, std::string const &cmd) {
		if(!(*this))
			return c;
		SQLRETURN ret = this->m_handle.check_error(::SQLExecDirect(this->m_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd.c_str())),
				SQL_NTS));
		if(SQL_SUCCEEDED(ret))
			c.m_stmt_ptr = this;
		return c;
	}

	cursor& statement::execute(cursor &c) {
		if(!(*this))
			return c;
		SQLRETURN ret = m_handle.check_error(::SQLExecute(this->m_handle.raw()));
		if(SQL_SUCCEEDED(ret))
			c.m_stmt_ptr = this;
		return c;
	}

	statement& statement::close_cursor() {
		//WARN: DO NOT throw any exception!!!
		m_handle.check_error(::SQLCloseCursor(m_handle.raw()));
		return *this;
	}

	int const statement::num_of_rs_cols() {
		SQLSMALLINT cols = -1;
		if (*this)
			m_handle.check_error(::SQLNumResultCols(m_handle.raw(), &cols));
		return cols;
	}

	string const statement::cursor_name() {
		string name;

		SQLRETURN retcode;
		char *buf = 0;
		SQLSMALLINT buf_len = 0;
		SQLSMALLINT out_len = 0;
		retcode = ::SQLGetCursorName(m_handle.raw(),
				reinterpret_cast<SQLCHAR*>(buf),
				buf_len,
				&out_len);
		if (!SQL_SUCCEEDED(retcode)) {
			m_handle.check_error(retcode);
			return std::move(name);
		}
		buf_len = out_len + (out_len % 2 ? 1 : 2);
		buf = new char[buf_len];
		retcode = m_handle.check_error(::SQLGetCursorName(m_handle.raw(),
				reinterpret_cast<SQLCHAR*>(buf),
				buf_len,
				&out_len));
		if (SQL_SUCCEEDED(retcode))
			name.assign(buf);
		delete[] buf;
		return std::move(name);
	}

	statement& statement::cursor_name(string const &name) {
		if (*this)
			m_handle.check_error(::SQLSetCursorName(m_handle.raw(),
						reinterpret_cast<SQLCHAR*>(const_cast<char*>(name.c_str())),
						SQL_NTS));
		return *this;
	}
}
