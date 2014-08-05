#ifndef ODBCXX_HANDLE_HPP_INCLUDED
#define ODBCXX_HANDLE_HPP_INCLUDED

#include "config.hpp"
#include "diaginfo.hpp"
#include <iosfwd>
#include <string>

namespace odbcxx {

    /**
     * The simulation of SQLHANDLE.
     */
	class handle {
		public:
            /**
             * The odbc handle types.
             */
			enum handle_type {
				ENV = SQL_HANDLE_ENV,
				DBC = SQL_HANDLE_DBC,
				STMT = SQL_HANDLE_STMT,
				DESC = SQL_HANDLE_DESC
			};

            /**
             * Function pointer for retreiving sql attributes.
             */
			typedef SQLRETURN (SQL_API *SQLATTRB_GETTER)(SQLHANDLE, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER*);
            /**
             * Function pointer for setting sql attributes.
             */
			typedef SQLRETURN (SQL_API *SQLATTRB_SETTER)(SQLHANDLE, SQLINTEGER, SQLPOINTER, SQLINTEGER);
		public:
			handle();
            /**
             * Construct handle object from specified SQLHANDLE and handle
             * type.
             * @param h SQLHANDLE value.
             * @param ht handle type.
             */
			handle(SQLHANDLE const h, SQLSMALLINT const ht);

            /**
             * Check whether this handle is valid.
             * @return true if it's not a null handle.
             */
			inline operator bool() const
			{ return m_handle != SQL_NULL_HANDLE; }

            /**
             * Check equality with other handle object.
             * @return true if it equals to the other one.
             */
			inline bool operator == (handle const& other) const
			{ return m_handle == other.m_handle && m_type == other.m_type; }
            /**
             * Check inequality with other handle object.
             * @return true if it DOES NOT equal to the other one.
             */
			inline bool operator != (handle const& other) const
			{ return !(*this == other); }

            /**
             * The common method for retreiving handle attribute.
             * @param attrb attribute indicator.
             * @param buf buffer for retreiving attribute value.
             * @param buf_len buffer size.
             * @param required_len the size needed for retreiving attribute
             * value.
             */
			SQLRETURN get_attribute(SQLINTEGER attrb, SQLPOINTER buf, SQLINTEGER buf_len, SQLINTEGER *required_len);
            /**
             * The common method for setting handle attribute.
             * @param attrb attribute indicator.
             * @param buf buffer which contains the attribute value.
             * @param buf_len buffer len indicator.
             */
			SQLRETURN set_attribute(SQLINTEGER attrb, SQLPOINTER buf, SQLINTEGER buf_len);

            /**
             * Retreive the underlying SQLHANDLE value.
             * @return SQLHANDLE value of this object.
             */
			inline SQLHANDLE const raw() const { return m_handle; }
            /**
             * Retreive the underlying SQLHANDLE type.
             * @return SQLHANDLE type of this object.
             */
			inline SQLSMALLINT const type() const { return m_type; }

            /**
             * The same as SQLAllocHandle.
             * @param type the next level handle type.
             * @return the next level handle object.
             */
			handle alloc(handle_type type);
            /**
             * Close this odbc handle.
             * @return SQL_SUCCESS if success.
             */
			SQLRETURN close();

            /**
             * The overload version of get_attrb which assumes the attribute
             * value type is SQLSMALLINT.
             * @param a attribute indicator.
             * @param v the variable for retrieve attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLSMALLINT &v)
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_SMALLINT, 0); }
            /**
             * The overload version of get_attrb which assumes the attribute
             * value type is SQLUSMALLINT.
             * @param a attribute indicator.
             * @param v the variable for retrieve attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLUSMALLINT &v)
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_USMALLINT, 0); }
            /**
             * The overload version of get_attrb which assumes the attribute
             * value type is SQLINTEGER.
             * @param a attribute indicator.
             * @param v the variable for retrieve attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLINTEGER &v)
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_INTEGER, 0); }
            /**
             * The overload version of get_attrb which assumes the attribute
             * value type is SQLUINTEGER.
             * @param a attribute indicator.
             * @param v the variable for retrieve attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN get_attrb(SQLINTEGER a, SQLUINTEGER &v)
			{ return get_attribute(a, reinterpret_cast<SQLPOINTER>(&v), SQL_IS_UINTEGER, 0); }
            /**
             * The overload version of get_attrb which assumes the attribute
             * value type is of std::string.
             * @param a attribute indicator.
             * @param v the variable for retrieve attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			SQLRETURN get_attrb(SQLINTEGER a, std::string &v);

            /**
             * The overload version of set_attrb which assumes the attribute
             * value type is SQLSMALLINT.
             * @param a attribute indicator.
             * @param v the variable contains attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLSMALLINT v)
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_SMALLINT); }
            /**
             * The overload version of set_attrb which assumes the attribute
             * value type is SQLUSMALLINT.
             * @param a attribute indicator.
             * @param v the variable contains attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLUSMALLINT v)
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_USMALLINT); }
            /**
             * The overload version of set_attrb which assumes the attribute
             * value type is SQLINTEGER.
             * @param a attribute indicator.
             * @param v the variable contains attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLINTEGER v)
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_INTEGER); }
            /**
             * The overload version of set_attrb which assumes the attribute
             * value type is SQLUINTEGER.
             * @param a attribute indicator.
             * @param v the variable contains attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN set_attrb(SQLINTEGER a, SQLUINTEGER v)
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(v), SQL_IS_UINTEGER); }
            /**
             * The overload version of set_attrb which assumes the attribute
             * value type is string.
             * @param a attribute indicator.
             * @param v the variable contains attribute value.
             * @param len indicate the string len.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN set_attrb(SQLINTEGER a, char const* v, SQLINTEGER len = SQL_NTS)
			{ return set_attribute(a, reinterpret_cast<SQLPOINTER>(const_cast<char*>(v)), len); }
            /**
             * The overload version of set_attrb which assumes the attribute
             * value type is null-terminated string.
             * @param a attribute indicator.
             * @param v the variable contains attribute value.
             * @return SQL_SUCCESS if succeed.
             */
			inline SQLRETURN set_attrb(SQLINTEGER a, std::string const& v)
			{ return set_attrb(a, v.c_str()); }

            /**
             * Retreive the diagnostic information about this handle.
             * @return SQL_SUCCESS or SQL_NO_DATA on success, and other values
             * for failure.
             */
			SQLRETURN diag(SQLSMALLINT, diaginfo&);

            /**
             * Check whether the SQLRETURN indicate operation success.
             * @param retcode if it is SQL_SUCCESS, nothing is done.
             * If it's SQL_INVALID_HANDLE, set current handle object to
             * handle::null.
             * If it's any other values, flush the diagnostic informations on
             * this handle.
             * @return the same as the input argument.
             */
			SQLRETURN check_error(SQLRETURN retcode);

            /**
             * Invalid handle object.
             */
			static handle null;
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
