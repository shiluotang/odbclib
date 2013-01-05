#ifndef ODBCXX_STATEMENT_HPP_INCLUDED
#define ODBCXX_STATEMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class resultset;
	class statement : public handle_object {
		public:
			statement& prepare(char const*);
			resultset& execute(resultset&, char const*);
			resultset& execute(resultset&);
		private:
			friend class session;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
