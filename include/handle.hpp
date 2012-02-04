#ifndef ODBCLIB_HANDLE_HPP_INCLUDED
#define ODBCLIB_HANDLE_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

#include "diaginfo.hpp"

NS_BEGIN_1(odbclib)

class Handle
{
	struct HandleInfo
	{
		HandleInfo(SQLSMALLINT type);
		SQLHANDLE m_handle;
		SQLSMALLINT m_type;
	}; 

	public:
		explicit Handle(Handle*,
			handletypes::HandleType);
		virtual ~Handle();		

		inline SQLHANDLE getHandle()const{return m_handleInfo.m_handle;}
		inline handletypes::HandleType getType()const
		{return static_cast<handletypes::HandleType>(m_handleInfo.m_type);}

		SQLRETURN getAttribute(SQLINTEGER ,SQLPOINTER ,SQLINTEGER ,SQLINTEGER*);

		inline SQLRETURN getAttribute(SQLINTEGER attrb,SQLSMALLINT& value)
		{return getAttribute(attrb,(SQLPOINTER)&value,SQL_IS_SMALLINT,0);}
		inline SQLRETURN getAttribute(SQLINTEGER attrb,SQLUSMALLINT& value)
		{return getAttribute(attrb,(SQLPOINTER)&value,SQL_IS_USMALLINT,0);}
		inline SQLRETURN getAttribute(SQLINTEGER attrb,SQLINTEGER& value)
		{return getAttribute(attrb,(SQLPOINTER)&value,SQL_IS_INTEGER,0);}
		inline SQLRETURN getAttribute(SQLINTEGER attrb,SQLUINTEGER& value)
		{return getAttribute(attrb,(SQLPOINTER)&value,SQL_IS_UINTEGER,0);}
		
		SQLRETURN setAttribute(SQLINTEGER ,SQLPOINTER ,SQLINTEGER);
		inline SQLRETURN setAttribute(SQLINTEGER attrb,SQLCHAR* array,SQLINTEGER len= SQL_NTS)
		{return setAttribute(attrb,(SQLPOINTER)array,len);}
		inline SQLRETURN setAttribute(SQLINTEGER attrb,SQLSMALLINT value)
		{return setAttribute(attrb,(SQLPOINTER)value,SQL_IS_SMALLINT);}
		inline SQLRETURN setAttribute(SQLINTEGER attrb,SQLUSMALLINT value)
		{return setAttribute(attrb,(SQLPOINTER)value,SQL_IS_USMALLINT);}
		inline SQLRETURN setAttribute(SQLINTEGER attrb,SQLINTEGER value)
		{return setAttribute(attrb,(SQLPOINTER)value,SQL_IS_INTEGER);}
		inline SQLRETURN setAttribute(SQLINTEGER attrb,SQLUINTEGER value)
		{return setAttribute(attrb,(SQLPOINTER)value,SQL_IS_UINTEGER);}

		void checkError(SQLRETURN);

	private:
		HandleInfo m_handleInfo;
		DiagInfo::DiagInfoEvent m_diagEvent;

		friend class Component;
};

NS_END_1

#endif
