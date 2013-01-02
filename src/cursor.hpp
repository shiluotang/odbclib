#ifndef ODBCLIB_CURSOR_HPP_INCLUDED
#define ODBCLIB_CURSOR_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

#include "component.hpp"
#include "transaction.hpp"

NS_BEGIN_1(odbclib)

class Statement;
class Cursor:
	protected Component,
	protected Transaction::TransactionEventListener
{
	public:
		explicit Cursor(Statement&);
		virtual ~Cursor();

		std::string getName();
		cursor::CursorType
		getType();
		cursor::CursorScrollable
		getScrollable();
		cursor::CursorSensitivity
		getSensitivity();
		cursor::CursorConcurrency
		getConcurrency();
		size_t getRowArraySize();
		void setRowArraySize(size_t);

		bool fetch(fetchtypes::FetchOrientation,
				fetchtypes::fetchoffset_t);
		bool fetchNext();
		bool fetchPrevious();
		bool fetchFirst();
		bool fetchLast();
		bool fetchRelative(fetchtypes::fetchoffset_t);
		bool fetchAbsolute(fetchtypes::fetchoffset_t);
		bool fetchBookmark();	

		SQLLEN getRowNumber();
		SQLULEN getFetchedRowCount();
	protected:
		virtual void doDispose();

		void setExternallyClosed();
		void onEvent(Transaction::TransactionEvent&,
				Transaction::TransactionEventArgs const&);
		
	private:
		Statement &m_stmt_ref;	
		SQLULEN m_fetchedRowsCnt;
		bool m_isExternallyClosed;
};

NS_END_1

#endif //ODBCLIB_CURSOR_HPP_INCLUDED
