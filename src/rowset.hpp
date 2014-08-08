#ifndef ODBCXX_ROWSET_HPP_INCLUDED
#define ODBCXX_ROWSET_HPP_INCLUDED

#include "config.hpp"

#include <cstddef>

namespace odbcxx {

	class statement;

	class rowset {
		public:
			explicit rowset(std::size_t columns_count = 0U, std::size_t capacity = 0U);
			std::size_t const capacity() const { return _M_capacity; }
			std::size_t const actual_size() const { return _M_actual_size; }
			std::size_t const columns_count() const { return _M_columns_count; }
			operator bool() const { return _M_columns_count > 0U
				&& _M_capacity > 0U && _M_actual_size > 0U; }
		protected:
			rowset& capacity(std::size_t c) { _M_capacity = c; return *this; }
			rowset& columns_count(std::size_t c) { _M_columns_count = c; return *this; }
		private:
			std::size_t _M_capacity;
			SQLUINTEGER _M_actual_size;
			size_t _M_columns_count;

			friend class statement;
			friend class cursor;
	};

}

#endif //ODBCXX_ROWSET_HPP_INCLUDED
