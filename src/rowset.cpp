#include "rowset.hpp"
#include "statement.hpp"

using namespace std;

namespace odbcxx {

	rowset::rowset(size_t columns_count,
			size_t capacity,
			size_t size,
			size_t position,
			statement *stmt_ptr)
		:_M_capacity(capacity),
		_M_size(size),
		_M_columns_count(columns_count),
		_M_position(position),
		_M_stmt_ptr(stmt_ptr)
   	{
	}

	rowset& rowset::position(size_t pos) {
		if (*this) {
			SQLRETURN retcode;
			retcode = _M_stmt_ptr->_M_handle.check_error(SQL_POSITION_TO(_M_stmt_ptr->_M_handle.raw(), pos));
			if (SQL_SUCCEEDED(retcode))
				_M_position = pos;
		}
		return *this;
	}

}
