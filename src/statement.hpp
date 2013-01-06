#ifndef ODBCXX_STATEMENT_HPP_INCLUDED
#define ODBCXX_STATEMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class cursor;
	class statement : public handle_object {
		public:
			void prepare(char const*);
			cursor& execute(cursor&, char const*);
			cursor& execute(cursor&);
		private:
			friend class session;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
