#ifndef ODBCXX_RESULTSET_HPP_INCLUDED
#define ODBCXX_RESULTSET_HPP_INCLUDED

#include "config.hpp"
#include "cursor.hpp"

namespace odbcxx {

	class cursor;
	class resultset {
		public:
			resultset& next();
		private:
			cursor _M_cursor;

			friend class cursor;
			friend class rowset;
	};

}

#endif //ODBCXX_RESULTSET_HPP_INCLUDED
