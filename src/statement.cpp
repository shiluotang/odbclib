#include "statement.hpp"
#include "session.hpp"
#include "cursor.hpp"
#include "buffer.hpp"

#include <string>
#include <cstring>

using namespace std;

namespace odbcxx {

	statement& statement::prepare(string const &cmd) {
		if (*this)
			_M_handle.throw_error(
					SQLPrepare(
						_M_handle.raw(),
						reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd.c_str())),
						SQL_NTS));
		return *this;
	}

	cursor& statement::execute(cursor &c, std::string const &cmd) {
		if (!(*this))
			return c;
		_M_handle.throw_error(
				::SQLExecDirect(
					_M_handle.raw(),
					reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd.c_str())),
					SQL_NTS));
		//check whether statement has opened cursor.
		int resultset_columns;
		//int resultset_rows;
		if ((resultset_columns = num_of_rs_cols()) > 0) {
			_M_handle.set_attrb(SQL_ATTR_ROWS_FETCHED_PTR, reinterpret_cast<SQLPOINTER>(&c._M_rowset._M_size));

			c._M_stmt_ptr = this;
			c._M_rowset.capacity(std::max(rowset_size(), 0));
			c._M_rowset.columns_count(resultset_columns);
		}
		return c;
	}

	cursor& statement::execute(cursor &c) {
		if (!(*this))
			return c;
		_M_handle.throw_error(::SQLExecute(_M_handle.raw()));
		//check whether statement has opened cursor.
		int resultset_columns;
		//int resultset_rows;
		if ((resultset_columns = num_of_rs_cols()) > 0) {
			_M_handle.set_attrb(SQL_ATTR_ROWS_FETCHED_PTR, &c._M_rowset._M_size);

			c._M_stmt_ptr = this;
			c._M_rowset.capacity(std::max(rowset_size(), 0));
			c._M_rowset.columns_count(resultset_columns);
		}
		return c;
	}

	statement& statement::close_cursor() {
		//WARN: DO NOT throw any exception!!!
		_M_handle.log_error(::SQLCloseCursor(_M_handle.raw()));
		return *this;
	}

	int const statement::num_of_rs_cols() {
		SQLSMALLINT cols = -1;
		_M_handle.throw_error(::SQLNumResultCols(_M_handle.raw(), &cols));
		return cols;
	}

	string const statement::cursor_name() {
		buffer buf(0);
		SQLSMALLINT out_len = 0;
		_M_handle.throw_error(::SQLGetCursorName(_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(buf.addr()), buf.size(),
				&out_len));
		buf.resize(out_len + 1);
		_M_handle.throw_error(::SQLGetCursorName(_M_handle.raw(),
				reinterpret_cast<SQLCHAR*>(buf.addr()), buf.size(),
				&out_len));
		return buf.addr();
	}

	statement& statement::cursor_name(string const &name) {
		if (*this)
			_M_handle.throw_error(::SQLSetCursorName(_M_handle.raw(),
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

	SQLRETURN statement::scroll(SQLSMALLINT orientation, SQLLEN offset) {
		SQLRETURN retcode = ::SQLFetchScroll(_M_handle.raw(),
					orientation, offset);
		if (retcode != SQL_NO_DATA) 
			_M_handle.throw_error(retcode);
		return retcode;
	}

	SQLRETURN statement::set_pos_in_rowset(SQLSETPOSIROW row,
			SQLUSMALLINT op,
			SQLUSMALLINT lock_type) {
		return _M_handle.throw_error(
				::SQLSetPos(
					_M_handle.raw(),
					row,
					op,
					lock_type));
	}

	SQLRETURN statement::bind_col(SQLUSMALLINT column_no,
			SQLSMALLINT target_type,
			SQLPOINTER target_value_ptr,
			SQLLEN buf_len,
			SQLLEN *len_or_indicator) {
		return _M_handle.throw_error(
				::SQLBindCol(
					_M_handle.raw(),
					column_no,
					target_type,
					target_value_ptr,
					buf_len,
					len_or_indicator));
	}

	SQLRETURN statement::get_data(SQLUSMALLINT no,
			SQLSMALLINT target_type,
			SQLPOINTER target_value_ptr,
			SQLLEN buf_len,
			SQLLEN *len_or_indicator) {
		return _M_handle.throw_error(
				::SQLGetData(
					_M_handle.raw(),
					no,
					target_type,
					target_value_ptr,
					buf_len,
					len_or_indicator));
	}

	SQLRETURN statement::get_data(SQLUSMALLINT no,
			SQLSMALLINT target_type,
			SQLPOINTER target_value_ptr,
			SQLLEN buf_len,
			bool &is_null) {
		SQLLEN indicator;
		SQLRETURN retcode = get_data(no,
				target_type,
				target_value_ptr,
				buf_len,
				&indicator);
		if (!SQL_SUCCEEDED(retcode))
			return retcode;
		is_null = (indicator == SQL_NULL_DATA);
		return retcode;
	}

	SQLRETURN statement::get_data(SQLUSMALLINT no, string &v, bool &is_null) {
		SQLRETURN retcode;
		char buf[4];
		SQLLEN buf_len = countof(buf) * sizeof(char);
		SQLLEN indicator = 0;

		string vv;

		while (true) {
			memset(buf, 0, sizeof(buf));
			retcode = ::SQLGetData(_M_handle.raw(), no, SQL_C_CHAR, &buf[0], buf_len, &indicator);
			// check null.
			if ((is_null = (indicator == SQL_NULL_DATA)))
				return retcode;
			// check no more data.
			if (retcode == SQL_NO_DATA)
				break;
			// check error.
			if (!SQL_SUCCEEDED(retcode))
				return _M_handle.throw_error(retcode);
			//concate data.
			vv.append(buf);
		}
		v = std::move(vv);
		return retcode;
	}
	SQLRETURN statement::get_data(SQLUSMALLINT no, wstring &v, bool &is_null) {
		SQLRETURN retcode;
		wchar_t buf[1024];
		SQLLEN buf_len = countof(buf) * sizeof(wchar_t);
		SQLLEN indicator = 0;

		wstring vv;
		//int bytes = 0;
		while (true) {
			memset(buf, 0, sizeof(buf));
			retcode = ::SQLGetData(_M_handle.raw(), no, SQL_C_WCHAR, &buf[0], buf_len, &indicator);
			// check null.
			if ((is_null = (indicator == SQL_NULL_DATA)))
				return retcode;
			// check no more data.
			if (retcode == SQL_NO_DATA)
				break;
			// check error.
			if (!SQL_SUCCEEDED(retcode))
				return _M_handle.log_error(retcode);
			//bytes = ((indicator > buf_len) || (indicator == SQL_NO_TOTAL)) ? buf_len : indicator;
			
			//concate data.
			vv.append(buf);
		}
		v = std::move(vv);
		return retcode;
	}
}
