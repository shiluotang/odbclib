#include "session.hpp"
#include "connection.hpp"
#include "statement.hpp"
#include "odbc_error.hpp"

#include <cstring>
#include <iostream>

using namespace std;

namespace odbcxx {

	session::session() :_M_conn_ptr(0) { std::memset(&_M_buf[0], 0, sizeof(_M_buf)); }

	session::~session() {
		try {
			close();
		} catch(odbc_error &e) {
			cerr << e.what() << endl;
		}
	}

	session::operator bool() const {
		return _M_conn_ptr != 0 && static_cast<bool>(*_M_conn_ptr);
	}

	session& session::close() {
		if (_M_conn_ptr) {
			_M_conn_ptr->disconnect();
			_M_conn_ptr = 0;
		}
		return *this;
	}

	statement& session::alloc(statement& stmt) {
		if (*this)
			stmt._M_handle = _M_conn_ptr->_M_handle.alloc(SQL_HANDLE_STMT);
		return stmt;
	}
}
