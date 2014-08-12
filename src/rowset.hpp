#ifndef ODBCXX_ROWSET_HPP_INCLUDED
#define ODBCXX_ROWSET_HPP_INCLUDED

#include "config.hpp"

#include <cstddef>

namespace odbcxx {

	class statement;
	class resultset;

	class rowset {
		public:
			explicit rowset(std::size_t columns_count = 0U,
					std::size_t capacity = 0U,
					std::size_t size = 0U,
					std::size_t position = 0U,
					statement *stmt_ptr = nullptr);
			std::size_t const capacity() const { return _M_capacity; }
			/**
			 * Tell the number of rows stored in current rowset.
			 * ATTENTION: It changes every single time the parent cursor take any movements.
			 * @return row counts contained in this rowset.
			 */
			std::size_t const size() const { return _M_size; }
			std::size_t const columns_count() const { return _M_columns_count; }
			operator bool() const {
				return _M_columns_count > 0U
					&& _M_capacity > 0U
					&& _M_size > 0U;
			}

			std::size_t position() const { return _M_position; }
		protected:
			rowset& capacity(std::size_t c) { _M_capacity = c; return *this; }
			rowset& columns_count(std::size_t c) { _M_columns_count = c; return *this; }
			rowset& position(std::size_t);
		private:
			std::size_t _M_capacity;
			SQLUINTEGER _M_size;
			std::size_t _M_columns_count;
			std::size_t _M_position;
			statement *_M_stmt_ptr;

			friend class statement;
			friend class cursor;
			friend class resultset;
	};

}

#endif //ODBCXX_ROWSET_HPP_INCLUDED
