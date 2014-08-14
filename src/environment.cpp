#include "environment.hpp"
#include "connection.hpp"

using namespace std;

namespace odbcxx {

	environment::environment(SQLINTEGER ver)
		:handle_object(handle::null.alloc(SQL_HANDLE_ENV)) {
		version(SQL_OV_ODBC3);
	}

	environment& environment::version(SQLINTEGER ver) {
		_M_handle.set_attrb(SQL_ATTR_ODBC_VERSION, ver);
		return *this;
	}
	SQLINTEGER environment::version() {
		SQLINTEGER ver;
		_M_handle.throw_error(
				_M_handle.get_attrb(
					SQL_ATTR_ODBC_VERSION,
					ver));
		return ver;
	}

	connection& environment::alloc(connection& conn) {
		conn._M_handle = _M_handle.alloc(SQL_HANDLE_DBC);
		return conn;
	}

	environment& environment::commit() {
		_M_handle.throw_error(::SQLEndTran(
					_M_handle.type(),
					_M_handle.raw(),
					SQL_COMMIT));
		return *this;
	}

	environment& environment::rollback() {
		_M_handle.throw_error(::SQLEndTran(
					_M_handle.type(),
					_M_handle.raw(),
					SQL_ROLLBACK));
		return *this;
	}
}
