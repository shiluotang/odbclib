#include "session.hpp"
#include "connection.hpp"
#include "statement.hpp"

#include <cstring>

using namespace std;

namespace odbcxx {

	session::session() :_M_conn_ptr(0) { memset(m_buf, 0, sizeof(m_buf)); }

	session::~session() { close(); }

	session::operator bool() const
	{ return _M_conn_ptr != 0 && static_cast<bool>(*_M_conn_ptr); }

	session& session::close() {
		if(_M_conn_ptr) {
			if(SQL_SUCCEEDED(_M_conn_ptr->disconnect()));
				_M_conn_ptr = 0;
		}
		return *this;
	}

	statement& session::alloc(statement& stmt) {
		if(*this)
			stmt._M_handle = _M_conn_ptr->_M_handle.alloc(handle::STMT);
		return stmt;
	}
}
