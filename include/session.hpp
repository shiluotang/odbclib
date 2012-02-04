#ifndef ODBCLIB_SESSION_HPP_INCLUDED
#define ODBCLIB_SESSION_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "component.hpp"

NS_BEGIN_1(odbclib)

class Connection;
class Transaction;
class Session:
	protected Component
{
	public:
		Session(Connection &,std::string const&);
		Session(Connection& ,
			std::string const&,
			std::string const&,
			std::string const&);
		virtual ~Session();
		inline Connection& getConnection()const{return m_conn_ref;}
		cursor::CursorBehavior getCursorBehavior(bool);
		size_t getConnectTimeout();
		std::string getCurrentCatalog();
		void commit();
		void rollback();
		
		inline
		std::string const&
		getOpenedConnectionString() const
		{return m_opened_connectionString;}

	protected:
		virtual void doDispose();

	private:
		Connection& m_conn_ref;
		std::string m_opened_connectionString;
		Transaction *m_tran_ptr;

		friend class Connection;
		friend class Transaction;
		friend class Statement;		
		friend class Cursor;
};	

NS_END_1

#endif //SESSION_HPP_INCLUDED
