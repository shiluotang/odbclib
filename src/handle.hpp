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
			handle();
			handle(SQLHANDLE const, SQLSMALLINT const);

			inline operator bool() const 
			{ return m_handle != SQL_NULL_HANDLE; }

			inline bool operator == (handle const& other) const
			{ return m_handle == other.m_handle && m_type == other.m_type; }
			inline bool operator != (handle const& other) const
			{ return !(*this == other); }

			SQLRETURN get_attribute(SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER*) const;
			SQLRETURN set_attribute(SQLINTEGER, SQLPOINTER, SQLINTEGER) const;

			inline SQLHANDLE const raw() const { return m_handle; }
			inline SQLSMALLINT const type() const { return m_type; }

			handle alloc(handle_type) const;
			SQLRETURN close() const;

			inline SQLRETURN get_attrb(SQLINTEGER a, SQLSMALLINT &v) const
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_SMALLINT, 0); }
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLUSMALLINT &v) const
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_USMALLINT, 0); }
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLINTEGER &v) const
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_INTEGER, 0); }
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLUINTEGER &v) const
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_UINTEGER, 0); }

			inline SQLRETURN set_attrb(SQLINTEGER a, SQLSMALLINT v) const
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_SMALLINT); }
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLUSMALLINT v) const
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_USMALLINT); }
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLINTEGER v) const
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_INTEGER); }
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLUINTEGER v) const
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_UINTEGER); }
			inline SQLRETURN set_attrb(SQLINTEGER a, char const* v, SQLINTEGER len = SQL_NTS) const
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(const_cast<char*>(v)), len); }
			inline SQLRETURN set_attrb(SQLINTEGER a, std::string const& v) const
			{ return set_attrb(a, v.c_str()); }

			SQLRETURN diag(SQLSMALLINT, diaginfo&) const;

			SQLRETURN check_error(SQLRETURN) const;

			static const handle& null;
		private:
			SQLHANDLE m_handle;
			SQLSMALLINT m_type;

			SQLATTRB_GETTER m_getter;
			SQLATTRB_SETTER m_setter;

			friend std::ostream& operator << (std::ostream&, handle const&);
	};

	std::ostream& operator << (std::ostream&, handle::handle_type);

}

#endif //ODBCX_HANDLE_HPP_INCLUDED
