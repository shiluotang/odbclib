#include "statement.hpp"
#include "session.hpp"
#include "connection.hpp"

using namespace std;

namespace odbcxx {

	void statement::prepare(char const* cmd) {
		if(*this)
			this->m_handle.check_error(::SQLPrepare(this->m_handle.raw(), 
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd)),
				SQL_NTS));
	}

	void statement::execute(char const* cmd) {
		if(*this)
			this->m_handle.check_error(::SQLExecDirect(this->m_handle.raw(), 
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd)),
				SQL_NTS));
	}
	void statement::execute() {
		if(*this)
			this->m_handle.check_error(::SQLExecute(this->m_handle.raw()));
	}
}
