#ifndef ODBCXX_CONNECTION_HPP_INCLUDED
#define ODBCXX_CONNECTION_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class environment;
	class session;
	class connection : public handle_object {
		public:
			connection();
			session& connect(session &s,
					char const*, 
					char const*, 
					char const*);
			/**
			 * output connection string is eliminated.
			 */
			session& driver_connect(session& s,
					char const*, 
					SQLUSMALLINT = SQL_DRIVER_NOPROMPT,
					SQLHWND = 0);
			/**
			 * output connection string is eliminated.
			 */
			session& browse_connect(session&, char const*);
		protected:
			inline SQLRETURN disconnect()
			{ 
				if(*this)
					return m_handle.check_error(SQLDisconnect(m_handle.raw())); 
				return SQL_SUCCESS;
			}

			friend class environment;
			friend class session;
			friend class statement;
	};

}

#endif //ODBCXX_CONNECTION_HPP_INCLUDED
