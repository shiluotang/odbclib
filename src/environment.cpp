#include "environment.hpp"
#include "connection.hpp"

using namespace std;

namespace odbcxx {

	environment::environment(environment::version ver) {
		this->_M_handle = handle::null.alloc(handle::ENV);
		set_version(ver);
	}

	void environment::set_version(environment::version ver) {
		SQLINTEGER v = static_cast<SQLINTEGER>(ver);
		this->_M_handle.set_attrb(SQL_ATTR_ODBC_VERSION, v);
	}

	connection& environment::alloc(connection& conn) {
		if(*this)
			conn._M_handle = this->_M_handle.alloc(handle::DBC);
		return conn;
	}

	SQLRETURN environment::commit() {
		if(*this)
			return _M_handle.check_error(::SQLEndTran(
					_M_handle.type(),
					_M_handle.raw(),
					SQL_COMMIT));
		return SQL_SUCCESS;
	}

	SQLRETURN environment::rollback() {
		if(*this)
			return _M_handle.check_error(::SQLEndTran(
					_M_handle.type(),
					_M_handle.raw(),
					SQL_ROLLBACK));
		return SQL_SUCCESS;
	}
}
