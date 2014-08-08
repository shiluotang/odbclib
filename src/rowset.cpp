#include "rowset.hpp"

using namespace std;

namespace odbcxx {

	rowset::rowset(size_t columns_count, size_t capacity)
		:_M_capacity(capacity), _M_columns_count(columns_count) { }

}
