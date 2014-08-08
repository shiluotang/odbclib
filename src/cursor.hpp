#ifndef ODBCXX_CURSOR_HPP_INCLUDED
#define ODBCXX_CURSOR_HPP_INCLUDED

#include "config.hpp"
#include "rowset.hpp"

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

			//movements
			cursor& next();
			cursor& prior();
			cursor& first();
			cursor& last();
			cursor& absolute(int offset);
			cursor& relative(int offset);
			cursor& bookmark(int offset);

			bool const bof() const { return _M_bof; }
			bool const eof() const { return _M_eof; }
		private:
			statement *m_stmt_ptr;
			rowset _M_rowset;
			bool _M_bof;
			bool _M_eof;

			friend class statement;
	};

}

#endif //ODBCXX_CURSOR_HPP_INCLUDED
