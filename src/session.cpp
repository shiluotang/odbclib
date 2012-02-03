#include "../include/connection.hpp"
#include "../include/session.hpp"
#include "../include/transaction.hpp"


using namespace std;

NS_BEGIN_1(odbclib)

Session::Session(Connection & conn,
		string const& connectionString)
try
	:m_conn_ref(conn),
	m_opened_connectionString(""),
	m_tran_ptr(0)
{
	DEBUG_INIT("Session");
	if(conn.m_session_ptr != 0)
		throw runtime_error("need to close previously connection before open");
	DEBUG_MSG("connection opening...");
	SQLRETURN ret = 0;	
	SQLCHAR connstr[0x1 << 10] = {0};
	SQLSMALLINT outlen;
	ret = SQLDriverConnect(conn.m_handle->getHandle(),0,
		(SQLCHAR*)connectionString.c_str(),SQL_NTS,
		connstr,sizeof(connstr),&outlen,SQL_DRIVER_NOPROMPT);
	conn.m_handle->checkError(ret);
	conn.addDisposingListener(*this);
	conn.m_session_ptr = this;
	m_opened_connectionString.assign((char const*)connstr);
}
catch(...)
{
	throw;
}

Session::Session(Connection& conn,string const& serverName,
		string const& userName,
		string const& authentication)
try
	:m_conn_ref(conn),
	m_opened_connectionString(""),
	m_tran_ptr(0)
{
	DEBUG_INIT("Session");
	if(conn.m_session_ptr != 0)
		throw runtime_error("need to close previously connection before open");
	DEBUG_MSG("connection opening...");
	SQLRETURN ret = SQLConnect(conn.m_handle->getHandle(),
		(SQLCHAR*)serverName.c_str(),SQL_NTS,
		(SQLCHAR*)userName.c_str(),SQL_NTS,
		(SQLCHAR*)authentication.c_str(),SQL_NTS);
	conn.m_handle->checkError(ret);
	conn.addDisposingListener(*this);
	conn.m_session_ptr = this;
}
catch(...)
{
	throw;
}

Session::~Session()
try
{
	DEBUG_RELEASE("Session");
	dispose();
}
catch(...){throw;}

void
Session::doDispose()
{
	DEBUG_MSG("connection closing...");
	SQLRETURN ret = SQLDisconnect(m_conn_ref.m_handle->getHandle());
	m_conn_ref.m_handle->checkError(ret);
	m_conn_ref.m_session_ptr = 0;
}

cursor::CursorBehavior
Session::getCursorBehavior(bool isCommit)
{
	SQLUSMALLINT cb = 0;
	SQLRETURN ret = m_conn_ref.getInfo(
		isCommit ? SQL_CURSOR_COMMIT_BEHAVIOR : SQL_CURSOR_ROLLBACK_BEHAVIOR,
		cb);
	m_conn_ref.m_handle->checkError(ret);
	return static_cast<cursor::CursorBehavior>(cb);
}

/**
 * Invalid option type will be result,if
 * SQL_ATTR_CONNECTION_TIMEOUT is requested
 * before connection is open
 */
size_t 
Session::getConnectTimeout()
{
	SQLUINTEGER timeout = 0;
	SQLRETURN ret = m_conn_ref.m_handle->getAttribute(
			SQL_ATTR_CONNECTION_TIMEOUT,
			timeout);
	m_conn_ref.m_handle->checkError(ret);
	return static_cast<SQLUINTEGER>(timeout);
}

string
Session::getCurrentCatalog()
{
	SQLCHAR buf[0xff] = {0};
	SQLINTEGER outLen = 0;
	SQLRETURN ret = m_conn_ref.m_handle->getAttribute(
			SQL_ATTR_CURRENT_CATALOG,
			buf,sizeof(buf),&outLen);
	m_conn_ref.m_handle->checkError(ret);
	return string(reinterpret_cast<char*>(&buf[0]));
}

void
Session::commit()
{
	SQLRETURN ret = SQLEndTran(m_conn_ref.m_handle->getType(),
		m_conn_ref.m_handle->getHandle(),SQL_COMMIT);
	m_conn_ref.m_handle->checkError(ret);
}

void
Session::rollback()
{
	SQLRETURN ret = SQLEndTran(m_conn_ref.m_handle->getType(),
		m_conn_ref.m_handle->getHandle(),SQL_ROLLBACK);
	m_conn_ref.m_handle->checkError(ret);
}

NS_END_1

