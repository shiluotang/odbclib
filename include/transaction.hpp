#ifndef ODBCLIB_TRANSACTION_HPP_INCLUDED
#define ODBCLIB_TRANSACTION_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

#include "component.hpp"

NS_BEGIN_1(odbclib)



class Session;
class Transaction
	:protected Component
{
	public:
		class TransactionEventArgs
		{
		public:
			TransactionEventArgs(Transaction &,bool);
			inline Transaction& getTransaction() const{return m_tran;}
			inline bool isCommit()const{return m_isCommit;}
			inline cursor::CursorBehavior
			getCursorBehavior()const{return m_cursorBehavior;}
		private:
			mutable Transaction &m_tran;
			bool m_isCommit;
			cursor::CursorBehavior m_cursorBehavior;
		};
		typedef utils::event::Event<TransactionEventArgs> TransactionEvent;
		typedef utils::event::EventListener<TransactionEventArgs> TransactionEventListener;
	public:
		explicit Transaction(Session&);
		virtual ~Transaction();
		inline Session& getSession(){return m_session_ref;}
		void commit();
		void rollback();
	protected:
		virtual void doDispose();

		TransactionEvent m_OnTransactionEnd;
	private:
		Session& m_session_ref;
		bool m_disposeByCommit;
		bool m_prev_autocommit_state;

		friend class Cursor;
};

NS_END_1

#endif //ODBCLIB_TRANSACTION_HPP_INCLUDED
