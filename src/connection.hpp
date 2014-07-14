#ifndef ODBCXX_CONNECTION_HPP_INCLUDED
#define ODBCXX_CONNECTION_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class environment;
	class session;
    /**
     * Standards for the connection handle.
     */
	class connection : public handle_object {
		public:
            /**
             * Construct an uninitialized connection handle.
             */
			connection();
            /**
             * Open connection.
             * @param s session object to indicate the opened connection.
             * @param server_name remote db server name could be a data source
             * name
             * @param user_name user name for authentication.
             * @param authentication password for authentication.
             */
			session& connect(session &s,
					std::string const &server_name,
					std::string const &user_name,
					std::string const &authentication);
			/**
			 * output connection string is eliminated.
             * @param s session object to indicate the opened connection.
             * @param in_connstr input connection string.
             * @param driver_completion driver completion level.
             * @param hwnd window handle.
			 */
			session& driver_connect(session &s,
					std::string const &in_connstr,
					SQLUSMALLINT driver_completion = SQL_DRIVER_NOPROMPT,
					SQLHWND hwnd = 0);
			/**
			 * output connection string is eliminated.
             * @param s session object to indicate the opened connection.
             * @param in_connstr input connection string.
			 */
			session& browse_connect(session &s,
                    std::string const &in_connstr);
		protected:
            /**
             * Disconnect current connection.
             * This is for internal use only.
             */
			SQLRETURN disconnect();

            /**
             * Commit all previously executed statements.
             * This is for internal use only.
             */
			SQLRETURN commit();
            /**
             * Rollback all previously executed statements.
             * This is for internal use only.
             */
			SQLRETURN rollback();

			friend class environment;
			friend class session;
			friend class statement;
	};

}

#endif //ODBCXX_CONNECTION_HPP_INCLUDED
