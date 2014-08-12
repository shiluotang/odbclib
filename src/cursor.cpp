#include "cursor.hpp"
#include "statement.hpp"

#include <utility>

using namespace std;

namespace odbcxx {

	cursor::cursor()
		:_M_stmt_ptr(0),
		_M_rowset(0),
		_M_bof(false),
		_M_eof(false)
	{}
	cursor::cursor(cursor &&other) :_M_stmt_ptr(0) {
		std::swap(_M_stmt_ptr, other._M_stmt_ptr);
	}
	cursor& cursor::operator = (cursor &&other) {
		if (this == &other)
			return *this;
		_M_stmt_ptr = other._M_stmt_ptr;
		other._M_stmt_ptr = 0;
		return *this;
	}
	cursor::operator bool() const {
		return _M_stmt_ptr != 0 && static_cast<bool>(*_M_stmt_ptr);
	}
	cursor::~cursor() { close(); }

	cursor& cursor::close() {
		if (_M_stmt_ptr) {
			_M_stmt_ptr->close_cursor();
			_M_stmt_ptr = 0;
			_M_rowset.capacity(0U);
			_M_bof = false;
			_M_eof = false;
		}
		return *this;
	}

	cursor& cursor::next() {
		if (*this) {
			if (!_M_eof) {
				if (_M_stmt_ptr->scroll(SQL_FETCH_NEXT, 0) == SQL_NO_DATA)
					_M_eof = true;
			}
		}
		return *this;
	}
	cursor& cursor::prior() {
		if (*this) {
			if (!_M_bof) {
				if (_M_stmt_ptr->scroll(SQL_FETCH_PRIOR, 0) == SQL_NO_DATA)
					_M_bof = true;
			}
		}
		return *this;
	}
	cursor& cursor::first() {
		if (*this) {
			if (!(_M_eof && _M_bof)) {
				if (_M_stmt_ptr->scroll(SQL_FETCH_FIRST, 0) == SQL_NO_DATA) {
					_M_eof = true;
					_M_bof = true;
				}
			}
		}
		return *this;
	}
	cursor& cursor::last() {
		if (*this) {
			if (!(_M_eof && _M_bof)) {
				if (_M_stmt_ptr->scroll(SQL_FETCH_LAST, 0) == SQL_NO_DATA) {
					_M_eof = true;
					_M_bof = true;
				}
			}
		}
		return *this;
	}
	cursor& cursor::absolute(int offset) {
		if (*this)
			_M_stmt_ptr->scroll(SQL_FETCH_ABSOLUTE, offset);
		return *this;
	}
	cursor& cursor::relative(int offset) {
		if (*this)
			_M_stmt_ptr->scroll(SQL_FETCH_RELATIVE, offset);
		return *this;
	}
	cursor& cursor::bookmark(int offset) {
		if (*this)
			_M_stmt_ptr->scroll(SQL_FETCH_BOOKMARK, offset);
		return *this;
	}
}
