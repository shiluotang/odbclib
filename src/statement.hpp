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

			/**
			 * Binds application data buffers to columns in the result set.
			 *
			 * @param column_no number of the result set column to bind. Columns
			 * are numbered in increasing column order starting at 0, where
			 * column 0 is the bookmark column. If bookmarks are not used --
			 * that is, the SQL_ATTR_USE_BOOKMARKS statement attribute is set to
			 * SQL_UB_OFF -- then column numbers start at 1.
			 *
			 * @param target_type The identifier of the C data type of the
			 * target_type buffer. When it is retrieving data from the data
			 * source with SQLFetch, SQLFetchScroll, SQLBulkOperations, or
			 * SQLSetPos, the driver converts the data to this type; when it
			 * sends data to the data source with SQLBulkOperations or
			 * SQLSetPos, the driver converts the data from this type. For a
			 * list of valid C data types and type identifiers, see the C Data
			 * Types section in Appendix D: Data Types.
			 * http://msdn.microsoft.com/en-us/library/ms714556%28v=vs.85%29.aspx
			 *
			 * @param target_value_ptr Pointer to the data buffer to bind to the
			 * column. SQLFetch and SQLFetchScroll return data in this buffer.
			 * SQLBulkOperations returns data in this buffer when Operation is
			 * SQL_FETCH_BOOKMARK; it retrieves data from this buffer when
			 * Operation is SQL_ADD or SQL_UPDATE_BY_BOOKMARK. SQLSetPos returns
			 * data in this buffer when Operation is SQL_REFRESH; it retrieves
			 * data from this buffer when Operation is SQL_UPDATE.
			 * If target_value_ptr is a null pointer, the driver unbinds the
			 * data buffer for the column. An application can unbind all columns
			 * by calling <code>SQLFreeStmt</code> with the SQL_UNBIND option.
			 * An application can unbind the data buffer for a column but still
			 * have a length/indicator ubffer bound for the column, if the
			 * target_value_ptr argument in the call to <code>SQLBindCol</code>
			 * is a null pointer but the len_or_indicator argument is a valid
			 * value.
			 *
			 * @param buf_len Length of the *target_value_ptr buffer in bytes.
			 * @param len_or_indicator Pointer to the length/indicator buffer to
			 * bind to the column.
			 */
			SQLRETURN bind_col(SQLUSMALLINT column_no,
					SQLSMALLINT target_type,
					SQLPOINTER target_value_ptr,
					SQLLEN buf_len,
					SQLLEN *len_or_indicator);

			SQLRETURN get_data(SQLUSMALLINT no,
					SQLSMALLINT target_type,
					SQLPOINTER target_value_ptr,
					SQLLEN buf_len,
					SQLLEN *len_or_indicator);
		private:
			friend class session;
			friend class cursor;
			friend class rowset;
	};

}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
