#ifndef ODBCXX_ENVIRONMENT_HPP_INCLUDED
#define ODBCXX_ENVIRONMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class connection;
    /**
     * Standards for SQL_HANDLE_ENV handle.
     */
	class environment : public handle_object {
		public:
			explicit environment(SQLINTEGER = SQL_OV_ODBC3);
			environment& version(SQLINTEGER);
			SQLINTEGER version();
			virtual ~environment() {}

			connection& alloc(connection &conn);

		protected:
			environment& commit();
			environment& rollback();

			friend class connection;
	};

}

#endif //ODBCXX_ENVIRONMENT_HPP_INCLUDED
