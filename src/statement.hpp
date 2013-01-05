#ifndef ODBCXX_STATEMENT_HPP_INCLUDED
#define ODBCXX_STATEMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class resultset;
	class statement : public handle_object {
		public:
			void prepare(char const*);
			void execute(char const*);
			void execute();
		private:
			friend class session;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
