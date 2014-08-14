#ifndef ODBCXX_STATEMENT_HPP_INCLUDED
#define ODBCXX_STATEMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class cursor;
	class rowset;

	class statement : public handle_object {
		public:
			statement& prepare(std::string const &cmd);
			cursor& execute(cursor &c, std::string const &cmd);
			cursor& execute(cursor &c);
			std::string const cursor_name();
			statement& cursor_name(std::string const& name);

		//protected:
		public:
			statement& close_cursor();
			int const num_of_rs_cols();

			int const rowset_size();
			statement& rowset_size(int);

			SQLRETURN scroll(SQLSMALLINT orientation, SQLLEN offset);
			SQLRETURN set_pos_in_rowset(SQLSETPOSIROW row, SQLUSMALLINT op,
					SQLUSMALLINT lock_type);

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

			SQLRETURN get_data(SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, bool&);
			SQLRETURN get_data(SQLUSMALLINT no, SQLSMALLINT &v, bool &is_null) {
				return get_data(no, SQL_C_SSHORT, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_SMALLINT, is_null);
			}
			SQLRETURN get_data(SQLUSMALLINT no, SQLUSMALLINT &v, bool &is_null) {
				return get_data(no, SQL_C_USHORT, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_USMALLINT, is_null);
			}
			SQLRETURN get_data(SQLUSMALLINT no, SQLINTEGER &v, bool &is_null) {
				return get_data(no, SQL_C_SLONG, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_INTEGER, is_null);
			}
			SQLRETURN get_data(SQLUSMALLINT no, SQLUINTEGER &v, bool &is_null) {
				return get_data(no, SQL_C_ULONG, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_UINTEGER, is_null);
			}
			SQLRETURN get_data(SQLUSMALLINT no, SQLREAL &v, bool &is_null) {
				return get_data(no, SQL_C_FLOAT, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_INTEGER, is_null);
			}
			SQLRETURN get_data(SQLUSMALLINT no, SQLDOUBLE &v, bool &is_null) {
				return get_data(no, SQL_C_DOUBLE, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_INTEGER, is_null);
			}
			SQLRETURN get_data(SQLUSMALLINT no, bool &v, bool &is_null) {
				SQLCHAR c;
				SQLRETURN retcode = get_data(no, SQL_C_BIT, reinterpret_cast<SQLPOINTER>(&c), 0, is_null);
				v = (c != 0);
				return retcode;
			}
			SQLRETURN get_data(SQLUSMALLINT no, std::string &v, bool &is_null);
			SQLRETURN get_data(SQLUSMALLINT no, std::wstring &v, bool &is_null);

		private:
			friend class session;
			friend class cursor;
			friend class rowset;
	};
}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
