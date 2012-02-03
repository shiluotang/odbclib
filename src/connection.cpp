#include "../include/environment.hpp"
#include "../include/connection.hpp"

#include <iostream>
using namespace std;

NS_BEGIN_1(odbclib)

Connection::Connection(Environment &env)
try	:m_env_ref(env),
	m_handle(new Handle(env.m_handle,
			odbclib::handletypes::Connection)),
	m_session_ptr(0)
{
	DEBUG_INIT("Connection");
	env.addDisposingListener(*this);
}
catch(...){throw;}

Connection::~Connection()
{
	DEBUG_RELEASE("Connection");
	dispose();
}

void
Connection::doDispose()
{
	delete m_handle;
}

void 
Connection::setAutocommit(bool autocommit)
{
	SQLRETURN ret = m_handle->setAttribute(
		SQL_ATTR_AUTOCOMMIT,
		static_cast<SQLSMALLINT>(autocommit ? 
			SQL_AUTOCOMMIT_ON : SQL_AUTOCOMMIT_OFF));
	m_handle->checkError(ret);
}

bool
Connection::getAutocommit()
{
	SQLUINTEGER ac = 0;
	SQLRETURN ret = m_handle->getAttribute(
		SQL_ATTR_AUTOCOMMIT,
		ac);
	m_handle->checkError(ret);
	return ac == SQL_AUTOCOMMIT_ON;
}

size_t 
Connection::getLoginTimeout()
{
	SQLUINTEGER timeout = 0u;
	SQLRETURN ret = m_handle->getAttribute(
			SQL_ATTR_LOGIN_TIMEOUT,
			timeout);
	m_handle->checkError(ret);
	return timeout;
}
void 
Connection::setLoginTimeout(size_t timeout)
{
	SQLRETURN ret = m_handle->setAttribute(
			SQL_ATTR_LOGIN_TIMEOUT,
			static_cast<SQLUINTEGER>(timeout));
	m_handle->checkError(ret);
}

void 
Connection::setConnectTimeout(size_t timeout)
{
	SQLRETURN ret = m_handle->setAttribute(
			SQL_ATTR_CONNECTION_TIMEOUT,
			static_cast<SQLUINTEGER>(timeout));
	m_handle->checkError(ret);
}
		
SQLRETURN
Connection::getInfo(SQLUSMALLINT infoType,
		SQLPOINTER infoValuePtr,
		SQLSMALLINT bufferLen,
		SQLSMALLINT* strLenPtr)
{
	SQLRETURN ret = SQLGetInfo(m_handle->getHandle(),
			infoType,
			infoValuePtr,bufferLen,
			strLenPtr);
	return ret;
}

SQLRETURN
Connection::getInfo(SQLUSMALLINT infoType,SQLUSMALLINT& value)
{return getInfo(infoType,(SQLPOINTER)&value,sizeof(SQLUSMALLINT),0);}

SQLRETURN 
Connection::getInfo(SQLUSMALLINT infoType,SQLUINTEGER& value)
{return getInfo(infoType,(SQLPOINTER)&value,sizeof(SQLUINTEGER),0);}

string
Connection::nativeSQL(string const& sql)
{
	SQLCHAR outSQL[0x1 << 10] = {0};
	SQLINTEGER len = 0;
	SQLRETURN ret = SQLNativeSql(m_handle->getHandle(),
		reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())),SQL_NTS,
		outSQL,sizeof(outSQL),&len);
	m_handle->checkError(ret);
	return string(reinterpret_cast<char*>(outSQL));
}

void
Connection::setCurrentCatalog(string const& catalogName)
{
	SQLRETURN ret = m_handle->setAttribute(
			SQL_ATTR_CURRENT_CATALOG,
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(catalogName.c_str())));
	m_handle->checkError(ret);
}

NS_END_1
