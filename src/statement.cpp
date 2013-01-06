#include "statement.hpp"
#include "session.hpp"
#include "cursor.hpp"

using namespace std;

namespace odbcxx {

	void statement::prepare(char const* cmd) {
		if(*this)
			this->m_handle.check_error(::SQLPrepare(this->m_handle.raw(), 
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd)),
				SQL_NTS));
	}

	cursor& statement::execute(cursor &c, char const* cmd) {
		if(!(*this))
			return c;
		SQLRETURN ret = this->m_handle.check_error(::SQLExecDirect(this->m_handle.raw(), 
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd)),
				SQL_NTS));
		if(SQL_SUCCEEDED(ret))
			c.m_stmt_ptr = this;
		return c;
	}
	cursor& statement::execute(cursor& c) {
		if(!(*this))
			return c;
		SQLRETURN ret = m_handle.check_error(::SQLExecute(this->m_handle.raw()));
		if(SQL_SUCCEEDED(ret))
			c.m_stmt_ptr = this;
		return c;
	}
}
