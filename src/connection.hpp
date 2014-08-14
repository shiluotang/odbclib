#ifndef ODBCXX_CONNECTION_HPP_INCLUDED
#define ODBCXX_CONNECTION_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class environment;
	class session;
	class connection : public handle_object {
		public:
			connection();
			session& connect(session&,
					std::string const &server_name,
					std::string const &user_name,
					std::string const &authentication);
			session& driver_connect(session&,
					std::string const &in_connstr,
					SQLUSMALLINT = SQL_DRIVER_NOPROMPT,
					SQLHWND = 0);
			session& browse_connect(session&,
                    std::string const &in_connstr);

			connection& current_catalog(std::string const&);
			std::string const current_catalog();

			bool auto_commit();
			connection& auto_commit(bool);

			std::string const native_sql(std::string const&);
		protected:
			connection& disconnect();

			connection& commit();
			connection& rollback();

			connection& get_info(SQLUSMALLINT, SQLSMALLINT&);
			connection& get_info(SQLUSMALLINT, SQLUSMALLINT&);
			connection& get_info(SQLUSMALLINT, SQLINTEGER&);
			connection& get_info(SQLUSMALLINT, SQLUINTEGER&);
			connection& get_info(SQLUSMALLINT, std::string&);

			friend class environment;
			friend class session;
			friend class statement;
	};

}

#endif //ODBCXX_CONNECTION_HPP_INCLUDED
