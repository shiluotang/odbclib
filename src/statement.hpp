#ifndef ODBCXX_STATEMENT_HPP_INCLUDED
#define ODBCXX_STATEMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class cursor;
	class rowset;

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
			/**
			 * Retrieve cursor name.
			 * @return cursor name.
			 */
			std::string const cursor_name();
			/**
			 * Set cursor name.
			 * @param name the name to be set.
			 * @return current statement object.
			 */
			statement& cursor_name(std::string const& name);

		protected:
			/**
			 * If there's any cursor open, close it.
			 * @return this statement object.
			 */
			statement& close_cursor();
			/**
			 * Retrieve column numbers of resultset.
			 * @return number of columns in current open resultset. If it's zero
			 * means no resultset. Minus means invokation failed.
			 */
			int const num_of_rs_cols();

			int const rowset_size();
			statement& rowset_size(int);

			/**
			 * Fetches the specified rowset of data from the result set and
			 * returns data for all bound columns.
			 * @param orientation as it says.
			 * @param offset as it says.
			 */
			SQLRETURN scroll(SQLSMALLINT orientation, SQLLEN offset);
			/**
			 * Set the cursor position in a rowset and allows an application to
			 * refresh data in the rowset or to update or delete data in the
			 * result set.
			 * @param row position of the row in the rowset on which to perform
			 * the operation specified with the op argument. If row is 0, the
			 * operation applies to every row in the rowset.
			 * @param op operation to perform. It can be SQL_POSITION,
			 * SQL_REFRESH, SQL_UPDATE, SQL_DELETE
			 * @param lock_type speicifies how to lock the row after performing
			 * the operation specified in the op argument.It can be one of
			 * these: SQL_LOCK_NO_CHANGE, SQL_LOCK_EXCLUSIVE, SQL_LOCK_UNLOCK
			 */
			SQLRETURN set_pos_in_rowset(SQLSETPOSIROW row, SQLUSMALLINT op,
					SQLUSMALLINT lock_type);

		private:
			friend class session;
			friend class cursor;
			friend class rowset;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
