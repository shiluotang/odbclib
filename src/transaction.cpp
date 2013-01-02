#include "connection.hpp"
#include "session.hpp"
#include "transaction.hpp"

using namespace odbclib;

Transaction::
TransactionEventArgs::TransactionEventArgs(Transaction& tran,
		bool isCommit)
try
	:m_tran(tran),
	m_isCommit(isCommit),
	m_cursorBehavior(tran.m_session_ref.getCursorBehavior(isCommit))
{
}
catch(...)
{throw;}

Transaction::Transaction(Session &session)
try
	:m_session_ref(session),
	m_disposeByCommit(true),
	m_prev_autocommit_state(session
			.getConnection()
			.getAutocommit())
{
	DEBUG_INIT("Transaction");
	if(m_prev_autocommit_state)
		session.getConnection().setAutocommit(false);
	session.addDisposingListener(*this);
	session.m_tran_ptr = this;
}
catch(...)
{
	throw;
}

Transaction::~Transaction()
{
	DEBUG_RELEASE("Transaction");
	dispose();
}

void
Transaction::doDispose()
{
	DEBUG_MSG("Transaction doDispose");
	if(m_disposeByCommit)
		m_session_ref.commit();
	else
		m_session_ref.rollback();
	m_session_ref.getConnection()
		.setAutocommit(m_prev_autocommit_state);
	m_OnTransactionEnd.occur(TransactionEventArgs(*this,m_disposeByCommit));
	m_session_ref.m_tran_ptr = 0;
}

void
Transaction::commit() 
{
	m_disposeByCommit = true;
	dispose();
}

void
Transaction::rollback() 
{
	m_disposeByCommit = false;
	dispose();
}
