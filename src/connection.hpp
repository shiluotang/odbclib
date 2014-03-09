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
					std::string const&, 
					std::string const&, 
					std::string const&);
			/**
			 * output connection string is eliminated.
			 */
			session& driver_connect(session& s,
					std::string const&,
					SQLUSMALLINT = SQL_DRIVER_NOPROMPT,
					SQLHWND = 0);
			/**
			 * output connection string is eliminated.
			 */
			session& browse_connect(session&, std::string const&);
		protected:
			SQLRETURN disconnect();

			SQLRETURN commit();
			SQLRETURN rollback();

			friend class environment;
			friend class session;
			friend class statement;
	};

}

#endif //ODBCXX_CONNECTION_HPP_INCLUDED
