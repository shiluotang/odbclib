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

			SQLRETURN bind_col(SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN*);

			statement& get_data(SQLUSMALLINT, SQLSMALLINT&,		bool&); 
			statement& get_data(SQLUSMALLINT, SQLUSMALLINT&,	bool&);
			statement& get_data(SQLUSMALLINT, SQLINTEGER&,		bool&);
			statement& get_data(SQLUSMALLINT, SQLUINTEGER&,		bool&);
			statement& get_data(SQLUSMALLINT, SQLREAL&,			bool&);
			statement& get_data(SQLUSMALLINT, SQLDOUBLE&,		bool&);
			statement& get_data(SQLUSMALLINT, SQLBIGINT&,		bool&);
			statement& get_data(SQLUSMALLINT, SQLUBIGINT&,		bool&);

			statement& get_data(SQLUSMALLINT, bool&,			bool&);
			statement& get_data(SQLUSMALLINT, std::string&,		bool&);
			statement& get_data(SQLUSMALLINT, std::wstring&,	bool&);

		private:
			friend class session;
			friend class cursor;
			friend class rowset;
	};
}

#endif //ODBCXX_STATEMENT_HPP_INCLUDED
