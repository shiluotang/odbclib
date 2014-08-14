#ifndef ODBCXX_HANDLE_HPP_INCLUDED
#define ODBCXX_HANDLE_HPP_INCLUDED

#include "config.hpp"
#include "diaginfo.hpp"
#include <iosfwd>
#include <string>

namespace odbcxx {

	class handle {
		public:
			typedef SQLRETURN (SQL_API *SQLATTRB_GETTER)(SQLHANDLE, SQLINTEGER,
					SQLPOINTER, SQLINTEGER, SQLINTEGER*);
			typedef SQLRETURN (SQL_API *SQLATTRB_SETTER)(SQLHANDLE, SQLINTEGER,
					SQLPOINTER, SQLINTEGER);
		public:
			explicit handle(SQLHANDLE = SQL_NULL_HANDLE, SQLSMALLINT = 0);
			operator bool() const { return _M_handle != SQL_NULL_HANDLE; }
			bool operator == (handle const& other) const {
				return _M_handle == other._M_handle
					&& _M_type == other._M_type;
			}
			bool operator != (handle const& other) const {
				return !(*this == other);
			}

			SQLHANDLE const raw() const { return _M_handle; }
			SQLSMALLINT const type() const { return _M_type; }

			handle alloc(SQLSMALLINT) const;
			void close();

			handle const& get_attrb(SQLINTEGER, SQLSMALLINT&)	const;
			handle const& get_attrb(SQLINTEGER, SQLUSMALLINT&)	const;
			handle const& get_attrb(SQLINTEGER, SQLINTEGER&)	const;
			handle const& get_attrb(SQLINTEGER, SQLUINTEGER&)	const;
			handle const& get_attrb(SQLINTEGER, std::string&)	const;
			handle const& get_attrb(SQLINTEGER, std::wstring&)	const;
			handle const& get_attrb(SQLINTEGER, SQLPOINTER&)	const;

			handle& set_attrb(SQLINTEGER, SQLSMALLINT);	
			handle& set_attrb(SQLINTEGER, SQLUSMALLINT);
			handle& set_attrb(SQLINTEGER, SQLINTEGER);
			handle& set_attrb(SQLINTEGER, SQLUINTEGER);
			handle& set_attrb(SQLINTEGER, SQLPOINTER);
			handle& set_attrb(SQLINTEGER, std::string const&);
			handle& set_attrb(SQLINTEGER, std::wstring const&);

			SQLRETURN diag(SQLSMALLINT, diaginfo&) const;
			handle const& log_error(SQLRETURN) const;
			handle const& ignore_error(SQLRETURN) const;
			handle const& throw_error(SQLRETURN) const;

			static const handle null;
		private:
			mutable SQLHANDLE _M_handle;
			SQLSMALLINT _M_type;

			SQLATTRB_GETTER _M_getter;
			SQLATTRB_SETTER _M_setter;

			friend std::ostream& operator << (std::ostream&, handle const&);
	};

	extern std::ostream& operator << (std::ostream&, handle const&);

}

#endif //ODBCX_HANDLE_HPP_INCLUDED
