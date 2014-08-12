#ifndef ODBCXX_HANDLE_HPP_INCLUDED
#define ODBCXX_HANDLE_HPP_INCLUDED

#include "config.hpp"
#include "diaginfo.hpp"
#include <iosfwd>
#include <string>

namespace odbcxx {

	class handle {
		public:
			enum handle_type {
				ENV = SQL_HANDLE_ENV,
				DBC = SQL_HANDLE_DBC,
				STMT = SQL_HANDLE_STMT,
				DESC = SQL_HANDLE_DESC
			};

			typedef SQLRETURN (SQL_API *SQLATTRB_GETTER)(SQLHANDLE, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER*);
			typedef SQLRETURN (SQL_API *SQLATTRB_SETTER)(SQLHANDLE, SQLINTEGER, SQLPOINTER, SQLINTEGER);
		public:
			handle(SQLHANDLE const = SQL_NULL_HANDLE, SQLSMALLINT const = 0);
			operator bool() const { return _M_handle != SQL_NULL_HANDLE; }
			bool operator == (handle const& other) const {
				return _M_handle == other._M_handle && _M_type == other._M_type;
			}
			bool operator != (handle const& other) const { return !(*this == other); }

			SQLHANDLE const raw() const { return _M_handle; }
			SQLSMALLINT const type() const { return _M_type; }

			handle alloc(SQLSMALLINT type);
			SQLRETURN close();

			SQLRETURN get_attrb(SQLINTEGER, SQLSMALLINT&);
			SQLRETURN get_attrb(SQLINTEGER, SQLUSMALLINT&);
			SQLRETURN get_attrb(SQLINTEGER, SQLINTEGER&);
			SQLRETURN get_attrb(SQLINTEGER, SQLUINTEGER&);
			SQLRETURN get_attrb(SQLINTEGER, std::string&);
			SQLRETURN get_attrb(SQLINTEGER, std::wstring&);

			SQLRETURN set_attrb(SQLINTEGER, SQLSMALLINT const&);
			SQLRETURN set_attrb(SQLINTEGER, SQLUSMALLINT const&);
			SQLRETURN set_attrb(SQLINTEGER, SQLINTEGER const&);
			SQLRETURN set_attrb(SQLINTEGER, SQLUINTEGER const&);
			SQLRETURN set_attrb(SQLINTEGER, SQLPOINTER);
			SQLRETURN set_attrb(SQLINTEGER, std::string const&);
			SQLRETURN set_attrb(SQLINTEGER, std::wstring const&);

			SQLRETURN diag(SQLSMALLINT, diaginfo&) const;
			SQLRETURN check_error(SQLRETURN retcode);
			SQLRETURN ignore_error(SQLRETURN retcode);

			static handle null;
		private:
			mutable SQLHANDLE _M_handle;
			SQLSMALLINT _M_type;

			SQLATTRB_GETTER _M_getter;
			SQLATTRB_SETTER _M_setter;

			friend std::ostream& operator << (std::ostream&, handle const&);
	};

	std::ostream& operator << (std::ostream&, handle::handle_type);

}

#endif //ODBCX_HANDLE_HPP_INCLUDED
