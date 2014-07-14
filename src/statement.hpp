#ifndef ODBCXX_STATEMENT_HPP_INCLUDED
#define ODBCXX_STATEMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class cursor;
    /**
     * The statement handle.
     */
	class statement : public handle_object {
		public:
            /**
             * Prepare sql command.
             * @param cmd sql command.
             */
			void prepare(std::string const &cmd);
            /**
             * Execute sql command.
             * @param c cursor object.
             * @param cmd sql command.
             * @return cursor object of the opened resultset.
             */
			cursor& execute(cursor &c, std::string const &cmd);
            /**
             * Execute the last prepared statement.
             * @param c cursor object.
             * @return cursor object of the opened resultset.
             */
			cursor& execute(cursor &c);
		private:
			friend class session;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
