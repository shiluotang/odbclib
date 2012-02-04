/*
 * Author:sqg
 * Date:2011/9/28
 * 
 * purpose:POD data type
 */
#ifndef ODBCLIB_COLUMNMETADATA_HPP_INCLUDED
#define ODBCLIB_COLUMNMETADATA_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

NS_BEGIN_1(odbclib)

class ColumnMetaData
{
	public:
		inline
		size_t getColumnNo()const{return m_no;}
		inline
		std::string const& 
		getName()const{return m_name;}
		inline
		odbclib::sqltypes::OdbcSQLType
		getSqlType()const{return m_sqlType;}
		inline
		size_t getSize()const{return m_size;}
		inline
		int getDecimalDigits()const{return m_decimalDigits;}
		inline
		int getNullable() const{return m_nullable;}
	private:
		SQLUSMALLINT m_no;
		std::string m_name;
		odbclib::sqltypes::OdbcSQLType
		m_sqlType;
		SQLULEN m_size;
		SQLSMALLINT m_decimalDigits;
		SQLSMALLINT m_nullable;
};

NS_END_1

#endif //ODBCLIB_COLUMNMETADATA_HPP_INCLUDED
