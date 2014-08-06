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
			 * @return current statement object.
             */
			statement& prepare(std::string const &cmd);
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
		protected:
			/**
			 * If there's any cursor open, close it.
			 * @return this statement object.
			 */
			statement& close_cursor();
			/**
			 * Retrieve column numbers of resultset.
			 * @return number of columns in current open resultset. If it's zero
			 * means no resultset.
			 */
			int const num_of_rs_cols();
			std::string const cursor_name();
			statement& cursor_name(std::string const&);
		private:
			friend class session;
			friend class cursor;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
