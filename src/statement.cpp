#include "statement.hpp"
#include "session.hpp"
#include "cursor.hpp"
#include <string>

using namespace std;

namespace odbcxx {

	statement& statement::prepare(string const &cmd) {
		if (*this)
			this->_M_handle.check_error(::SQLPrepare(this->_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd.c_str())),
				SQL_NTS));
		return *this;
	}

	cursor& statement::execute(cursor &c, std::string const &cmd) {
		if (!(*this))
			return c;
		SQLRETURN ret = this->_M_handle.check_error(::SQLExecDirect(this->_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd.c_str())),
				SQL_NTS));
		if (!SQL_SUCCEEDED(ret))
			return c;
		//check whether statement has opened cursor.
		int resultset_columns;
		int resultset_rows;
		if ((resultset_columns = num_of_rs_cols()) > 0) {
			c._M_rowset.capacity(std::max(rowset_size(), 0));
			if (SQL_SUCCEEDED(_M_handle.set_attribute(SQL_ATTR_ROWS_FETCHED_PTR,
					&c._M_rowset._M_actual_size, SQL_IS_UINTEGER))) {
				c.m_stmt_ptr = this;
				c._M_rowset.capacity(std::max(rowset_size(), 0));
				c._M_rowset.columns_count(resultset_columns);
			}
		}
		return c;
	}

	cursor& statement::execute(cursor &c) {
		if (!(*this))
			return c;
		SQLRETURN ret = _M_handle.check_error(::SQLExecute(this->_M_handle.raw()));
		if (!SQL_SUCCEEDED(ret))
			return c;
		//check whether statement has opened cursor.
		int resultset_columns;
		int resultset_rows;
		if ((resultset_columns = num_of_rs_cols()) > 0) {
			if (SQL_SUCCEEDED(_M_handle.set_attribute(SQL_ATTR_ROWS_FETCHED_PTR,
					&c._M_rowset._M_actual_size, SQL_IS_UINTEGER))) {
				c.m_stmt_ptr = this;
				c._M_rowset.capacity(std::max(rowset_size(), 0));
				c._M_rowset.columns_count(resultset_columns);
			}
		}
		return c;
	}

	statement& statement::close_cursor() {
		//WARN: DO NOT throw any exception!!!
		_M_handle.check_error(::SQLCloseCursor(_M_handle.raw()));
		return *this;
	}

	int const statement::num_of_rs_cols() {
		SQLSMALLINT cols = -1;
		if (*this)
			_M_handle.check_error(::SQLNumResultCols(_M_handle.raw(), &cols));
		return cols;
	}

	string const statement::cursor_name() {
		string name;

		SQLRETURN retcode;
		char *buf = 0;
		SQLSMALLINT buf_len = 0;
		SQLSMALLINT out_len = 0;
		retcode = ::SQLGetCursorName(_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(buf),
				buf_len,
				&out_len);
		if (!SQL_SUCCEEDED(retcode)) {
			_M_handle.check_error(retcode);
			return std::move(name);
		}
		buf_len = out_len + (out_len % 2 ? 1 : 2);
		buf = new char[buf_len];
		retcode = _M_handle.check_error(::SQLGetCursorName(_M_handle.raw(),
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
			_M_handle.check_error(::SQLSetCursorName(_M_handle.raw(),
						reinterpret_cast<SQLCHAR*>(const_cast<char*>(name.c_str())),
						SQL_NTS));
		return *this;
	}

	int const statement::rowset_size() {
		SQLUINTEGER sz = -1;
		_M_handle.get_attrb(SQL_ATTR_ROW_ARRAY_SIZE, sz);
		return sz == static_cast<SQLUINTEGER>(-1) ? -1 : sz;
	}

	statement& statement::rowset_size(int size) {
		SQLUINTEGER sz = size;
		_M_handle.set_attrb(SQL_ATTR_ROW_ARRAY_SIZE, sz);
		return *this;
	}

	SQLRETURN statement::scroll(SQLSMALLINT orientation, SQLINTEGER offset) {
		return _M_handle.check_error(::SQLFetchScroll(_M_handle.raw(),
					orientation, offset));
	}

	SQLRETURN statement::set_pos_in_rowset(SQLSETPOSIROW row,
			SQLUSMALLINT op,
			SQLUSMALLINT lock_type) {
		return _M_handle.check_error(::SQLSetPos(_M_handle.raw(),
					row, op, lock_type));
	}

	SQLRETURN statement::bind_col(SQLUSMALLINT column_no,
			SQLSMALLINT target_type,
			SQLPOINTER target_value_ptr,
			SQLINTEGER buf_len,
			SQLINTEGER *len_or_indicator) {
		return _M_handle.check_error(::SQLBindCol(_M_handle.raw(),
					column_no,
					target_type,
					target_value_ptr,
					buf_len,
					len_or_indicator));
	}
}
