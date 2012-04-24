#include "../include/connection.hpp"
#include "../include/session.hpp"
#include "../include/statement.hpp"
#include "../include/cursor.hpp"

using namespace std;

NS_BEGIN_1(odbclib)

Statement::Statement(Session &session)
try
	:m_session_ref(session),
	m_handle(new Handle(session.m_conn_ref.m_handle,handle::Statement)),
	m_prepared(false),
	m_cursor_ptr(0)
{
	DEBUG_INIT("Statement");
}
catch(...)
{
	doDispose();
	throw;
}

Statement::~Statement()
{
	DEBUG_RELEASE("Statement");
	dispose();
}

void
Statement::doDispose()
{
	DEBUG_MSG("Statement doDispose");
	delete m_cursor_ptr;
	m_cursor_ptr = 0;
	delete m_handle;
	m_handle = 0;
	m_prepared = false;
}

void
Statement::setCursorName(string const& cursorName)
{
	SQLRETURN ret = 
		SQLSetCursorName(m_handle->getHandle(),
			reinterpret_cast<SQLCHAR*>(const_cast<char*>(cursorName.c_str())),
			SQL_NTS);
	m_handle->checkError(ret);
}

string
Statement::getCursorName()
{
	SQLCHAR buf[0xff] = {0};
	SQLSMALLINT outLen = 0;
	SQLRETURN ret = 
		SQLGetCursorName(m_handle->getHandle(),
			buf,sizeof(buf),&outLen);
	m_handle->checkError(ret);
	return string(reinterpret_cast<char*>(buf));
}

void
Statement::setCursorType(cursor::CursorType ct)
{	
	SQLRETURN ret = m_handle->setAttribute(
		SQL_ATTR_CURSOR_TYPE,
		static_cast<SQLUINTEGER>(ct));
	m_handle->checkError(ret);
}

void
Statement::setCursorScrollable(cursor::CursorScrollable cs)
{
	SQLRETURN ret = m_handle->setAttribute(
		SQL_ATTR_CURSOR_SCROLLABLE,
		static_cast<SQLUINTEGER>(cs));
	m_handle->checkError(ret);
}

void
Statement::setCursorSensitivity(cursor::CursorSensitivity cs)
{
	SQLRETURN ret = m_handle->setAttribute(
		SQL_ATTR_CURSOR_SENSITIVITY,
		static_cast<SQLUINTEGER>(cs));
	m_handle->checkError(ret);
}

void
Statement::setCursorConcurrency(cursor::CursorConcurrency cc)
{
	SQLRETURN ret = m_handle->setAttribute(
		SQL_ATTR_CONCURRENCY,
		static_cast<SQLUINTEGER>(cc));
	m_handle->checkError(ret);
}

void
Statement::setCursorRowArraySize(size_t sz)
{
	SQLRETURN ret = m_handle->setAttribute(
		SQL_ATTR_ROW_ARRAY_SIZE,
		static_cast<SQLUINTEGER>(sz));
	m_handle->checkError(ret);
}

cursor::CursorType
Statement::getCursorType()
{
	SQLUINTEGER ct = 0;
	SQLRETURN ret = m_handle->getAttribute(
			SQL_ATTR_CURSOR_TYPE,
			ct);
	m_handle->checkError(ret);
	return static_cast<cursor::CursorType>(ct);
}

cursor::CursorScrollable
Statement::getCursorScrollable()
{
	SQLUINTEGER cs = 0;
	SQLRETURN ret = m_handle->getAttribute(
			SQL_ATTR_CURSOR_SCROLLABLE,
			cs);
	m_handle->checkError(ret);
	return static_cast<cursor::CursorScrollable>(cs);
}

cursor::CursorSensitivity
Statement::getCursorSensitivity()
{
	SQLUINTEGER cs = 0;
	SQLRETURN ret = m_handle->getAttribute(
			SQL_ATTR_CURSOR_SENSITIVITY,
			cs);
	m_handle->checkError(ret);
	return static_cast<cursor::CursorSensitivity>(cs);
}

cursor::CursorConcurrency
Statement::getCursorConcurrency()
{
	SQLUINTEGER cc = 0;
	SQLRETURN ret = m_handle->getAttribute(
			SQL_ATTR_CONCURRENCY,
			cc);
	m_handle->checkError(ret);
	return static_cast<cursor::CursorConcurrency>(cc);
}

size_t
Statement::getCursorRowArraySize()
{
	SQLUINTEGER sz = 0;
	SQLRETURN ret = m_handle->getAttribute(
			SQL_ATTR_ROW_ARRAY_SIZE,
			sz);
	m_handle->checkError(ret);
	return static_cast<size_t>(sz);
}

void
Statement::prepare(string const& sql)
{
	SQLRETURN ret = SQLPrepare(
		m_handle->getHandle(),
		reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())),
		SQL_NTS);
	m_handle->checkError(ret);
	m_preparedsql = sql;
	m_prepared = true;
}

void
Statement::execute()
{
	if(!m_prepared)
		throw runtime_error("need prepare() first!");
	closeCursor();
	DEBUG_MSG((string("executing prepared statement:") + m_preparedsql).c_str());
	SQLRETURN ret = SQLExecute(m_handle->getHandle());
	m_handle->checkError(ret);
	if(hasResultSet())
		m_cursor_ptr = new Cursor(*this);
}

void
Statement::execute(string const& sql)
{
	closeCursor();
	DEBUG_MSG((string("directly executing statement:") + sql).c_str());
	SQLRETURN ret = SQLExecDirect(m_handle->getHandle(),
		reinterpret_cast<SQLCHAR*>(const_cast<char*>(sql.c_str())),
		SQL_NTS);
	m_handle->checkError(ret);
	if(hasResultSet())
		m_cursor_ptr = new Cursor(*this);
}

void
Statement::closeCursor()
{
	delete m_cursor_ptr;
	m_cursor_ptr = 0;
}

void
Statement::cancel()
{
	SQLRETURN ret = SQLCancel(m_handle->getHandle());
	m_handle->checkError(ret);
}

bool
Statement::hasResultSet()
{
	SQLSMALLINT colcnt = 0;
	SQLRETURN ret = SQLNumResultCols(
		m_handle->getHandle(),
		&colcnt);
	m_handle->checkError(ret);
	return colcnt > 0;
}

SQLLEN
Statement::getAffectedRowCount()
{
	SQLLEN rowcnt = 0;
	SQLRETURN ret = SQLRowCount(
		m_handle->getHandle(),
		&rowcnt);
	m_handle->checkError(ret);
	return rowcnt;
}

NS_END_1
