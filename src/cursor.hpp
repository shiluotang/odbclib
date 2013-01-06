#ifndef ODBCXX_CURSOR_HPP_INCLUDED
#define ODBCXX_CURSOR_HPP_INCLUDED

#include "config.hpp"

namespace odbcxx {

	class statement;
	class cursor {
		public:
			cursor();
			~cursor();

			operator bool() const;
		private:
			statement *m_stmt_ptr;

			friend class statement;
	};

}

#endif //ODBCXX_CURSOR_HPP_INCLUDED
