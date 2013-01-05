#include "statement.hpp"
#include "session.hpp"
#include "connection.hpp"

using namespace std;

namespace odbcxx {

	statement& statement::prepare(char const* cmd) {
		this->m_handle.check_error(::SQLPrepare(this->m_handle.raw(), 
				reinterpret_cast<SQLCHAR*>(const_cast<char*>(cmd)),
				SQL_NTS));
		return *this;
	}

}
