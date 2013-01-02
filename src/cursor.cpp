#include "session.hpp"
#include "statement.hpp"
#include "cursor.hpp"

using namespace std;
using namespace odbclib::fetchtypes;

NS_BEGIN_1(odbclib)

Cursor::Cursor(Statement& stmt)
try
	:m_stmt_ref(stmt),
	m_fetchedRowsCnt(0),
	m_isExternallyClosed(false)
{
	DEBUG_INIT("Cursor");
	if(stmt.m_cursor_ptr != 0)
		throw runtime_error("cursor already in use!");
	SQLRETURN ret =	stmt.m_handle->setAttribute(
		SQL_ATTR_ROWS_FETCHED_PTR,
		&m_fetchedRowsCnt,SQL_IS_POINTER);
	stmt.m_handle->checkError(ret);
	stmt.addDisposingListener(*this);
	stmt.m_cursor_ptr = this;
	Transaction *tran = 0;
	if((tran = stmt.getSession().m_tran_ptr) != 0)
		tran->m_OnTransactionEnd.addListener(*this);
}
catch(...)
{
	throw;
}

Cursor::~Cursor()
{
	DEBUG_RELEASE("Cursor");
	dispose();
}

void
Cursor::doDispose()
{
	if(m_isExternallyClosed)
		return;
	DEBUG_MSG("cursor closing...");
	//kb201110241941
	/*
	SQLRETURN ret = SQLFreeStmt(
			m_stmt_ref.m_handle->getHandle(),
			SQL_CLOSE);
	*/
	//bug 201110241941
	//if there's no cursor open,SQLCloseCursor will
	//result in an error for invalid cursor state, 
	//24000
	SQLRETURN ret = SQLCloseCursor(
		m_stmt_ref.m_handle->getHandle());
	m_stmt_ref.m_handle->checkError(ret);
	m_stmt_ref.m_cursor_ptr = 0;
}

void Cursor::setExternallyClosed(){ m_isExternallyClosed = true; }

string Cursor::getName() { return m_stmt_ref.getCursorName(); }
cursor::CursorType Cursor::getType() { return m_stmt_ref.getCursorType(); }
cursor::CursorScrollable Cursor::getScrollable() { return m_stmt_ref.getCursorScrollable(); }
cursor::CursorSensitivity Cursor::getSensitivity() { return m_stmt_ref.getCursorSensitivity(); }
cursor::CursorConcurrency Cursor::getConcurrency() { return m_stmt_ref.getCursorConcurrency(); }
size_t Cursor::getRowArraySize() { return m_stmt_ref.getCursorRowArraySize();}
void Cursor::setRowArraySize(size_t sz){m_stmt_ref.setCursorRowArraySize(sz);}

bool
Cursor::fetch(FetchOrientation fetchType,
		fetchoffset_t offset)
{
	SQLRETURN ret = SQLFetchScroll(
			m_stmt_ref.m_handle->getHandle(),
			static_cast<SQLSMALLINT>(fetchType),
			offset);
	if(ret == SQL_NO_DATA)
		return false;
	m_stmt_ref.m_handle->checkError(ret);
	return true;
}

bool Cursor::fetchNext(){return fetch(Next,0);}
bool Cursor::fetchPrevious(){return fetch(Previous,0);}
bool Cursor::fetchFirst(){return fetch(First,0);}
bool Cursor::fetchLast(){return fetch(Last,0);}
bool Cursor::fetchRelative(fetchoffset_t offset){return fetch(Relative,offset);}
bool Cursor::fetchAbsolute(fetchoffset_t offset){return fetch(Absolute,offset);}
bool Cursor::fetchBookmark(){return fetch(Bookmark,0);}

SQLLEN
Cursor::getRowNumber()
{
	SQLUINTEGER rowno = 0;
	SQLRETURN ret = m_stmt_ref.m_handle->getAttribute(
			SQL_ATTR_ROW_NUMBER,
			rowno);
	m_stmt_ref.m_handle->checkError(ret);
	return rowno;
}

SQLULEN
Cursor::getFetchedRowCount() { return m_fetchedRowsCnt; }

void
Cursor::onEvent(Transaction::TransactionEvent &e,
		Transaction::TransactionEventArgs const& args)
{
	if(&args.getTransaction().getSession().m_conn_ref
			!= &m_stmt_ref.getSession().m_conn_ref)
		return;
	switch(args.getCursorBehavior())
	{
		case cursor::Preserve:
			break;
		case cursor::Delete:
			m_stmt_ref.m_prepared = false;
		case cursor::Close:
			setExternallyClosed();
			m_stmt_ref.closeCursor();
			break;
		default:break;
	}
}

NS_END_1

