#ifndef ODBCXX_CURSOR_HPP_INCLUDED
#define ODBCXX_CURSOR_HPP_INCLUDED

#include "config.hpp"

namespace odbcxx {

	class statement;
    /**
     * The Cursor object associated with an opened result set.
     */
	class cursor {
		public:
			cursor();
			cursor(cursor const&) = delete;
			cursor(cursor &&);
			cursor& operator = (cursor const&) = delete;
			cursor& operator = (cursor &&);
			~cursor();

            /**
             * Check whether this cursor is valid.
             * @return true if it's valid, vice versa.
             */
			operator bool() const;
			cursor& close();
		private:
			statement *m_stmt_ptr;

			friend class statement;
	};

}

#endif //ODBCXX_CURSOR_HPP_INCLUDED
