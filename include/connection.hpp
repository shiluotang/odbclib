#ifndef ODBCLIB_CONNECTION_HPP_INCLUDED
#define ODBCLIB_CONNECTION_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

#include "component.hpp"
#include <string>

NS_BEGIN_1(odbclib)

class Environment;
class Session;
class Connection
	:public Component
{
	public:
		explicit Connection(Environment &);
		virtual ~Connection();

		bool getAutocommit();
		void setAutocommit(bool);
		size_t getLoginTimeout();
		void setLoginTimeout(size_t);
		void setConnectTimeout(size_t);		
		void setCurrentCatalog(std::string const&);
		std::string nativeSQL(std::string const&);
	protected:
		SQLRETURN getInfo(SQLUSMALLINT,SQLPOINTER,SQLSMALLINT,SQLSMALLINT*);
		SQLRETURN getInfo(SQLUSMALLINT,SQLUSMALLINT&);
		SQLRETURN getInfo(SQLUSMALLINT,SQLUINTEGER&);
	protected:
		virtual void doDispose();
	private:
		Environment 	&m_env_ref;
		Handle 		*m_handle;
		Session 	*m_session_ptr;

		friend class Session;
		friend class Transaction;
		friend class Statement;
};

NS_END_1

#endif
