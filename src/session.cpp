#include "session.hpp"
#include "connection.hpp"
#include "statement.hpp"

#include <cstring>

using namespace std;

namespace odbcxx {

	session::session() 
		:m_conn_ptr(0)
       	{ memset(m_buf, 0, sizeof(m_buf)); }

	session::~session() { close(); }

	session& session::close() {
		if(m_conn_ptr) {
			if(SQL_SUCCEEDED(m_conn_ptr->disconnect()));
				m_conn_ptr = 0;
		}
		return *this;
	}

	statement& session::alloc(statement& s) {
		if(*this)
			s.m_handle = m_conn_ptr->m_handle.alloc(handle::STMT);
		return s;
	}
}
