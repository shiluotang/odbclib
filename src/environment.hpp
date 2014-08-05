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
            /**
             * The odbc versions.
             */
			enum version {
				OV2 = SQL_OV_ODBC2,
				OV3 = SQL_OV_ODBC3
			};
		public:
            /**
             * Construct odbc environement handle from specified version.
             * @param ver odbc version.
             */
			explicit environment(version ver = OV3);
            /**
             * Change current odbc version.
             * @param ver the required odbc version.
             */
			void set_version(version ver);
			virtual ~environment() {}

            /**
             * Allocate next level handle, the odbc connection handle.
             * @param conn uninitialized connection handle.
             * @return the same as input parameter, but as it has implicit
             * conversion to bool, it can be used to detect whether this
             * function worked properly.
             */
			connection& alloc(connection &conn);

		protected:
            /**
             * Commit all the uncommitted statements which're associated with
             * this environment handle. This is for internal use only.
             * @return SQL_SUCCESS if success.
             */
			SQLRETURN commit();
            /**
             * Rollback all the uncommitted statements which're associated
             * with this environment handle. This is for internal use only.
             * @return SQL_SUCCESS if success.
             */
			SQLRETURN rollback();

			friend class connection;
	};

}

#endif //ODBCXX_ENVIRONMENT_HPP_INCLUDED
