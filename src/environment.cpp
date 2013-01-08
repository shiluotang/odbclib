#include "environment.hpp"
#include "connection.hpp"

using namespace std;

namespace odbcxx {

	environment::environment(environment::version ver) {
		this->m_handle = handle::null.alloc(handle::ENV);
		set_version(ver);
	}

	void environment::set_version(environment::version ver) {
		SQLINTEGER v = static_cast<SQLINTEGER>(ver);
		this->m_handle.set_attrb(SQL_ATTR_ODBC_VERSION, v);
	}

	connection& environment::alloc(connection& conn) {
		if(*this)
			conn.m_handle = this->m_handle.alloc(handle::DBC);
		return conn;
	}

	SQLRETURN environment::commit() {
		if(*this)
			return m_handle.check_error(::SQLEndTran(
					m_handle.type(),
					m_handle.raw(),
					SQL_COMMIT));
		return SQL_SUCCESS;
	}

	SQLRETURN environment::rollback() {
		if(*this)
			return m_handle.check_error(::SQLEndTran(
					m_handle.type(),
					m_handle.raw(),
					SQL_ROLLBACK));
		return SQL_SUCCESS;
	}
}
