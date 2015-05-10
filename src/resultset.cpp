#include "resultset.hpp"
#include "statement.hpp"
#include "cursor.hpp"
#include "rowset.hpp"

using namespace std;

namespace odbcxx {

	resultset& resultset::next() {
		if (_M_cursor.next()) {
			if (_M_cursor._M_rowset.position() < _M_cursor._M_rowset.size())
				_M_cursor._M_rowset.position(_M_cursor._M_rowset.position() + 1);
		}
		return *this;
	}

}
