#ifndef ODBCXX_SESSION_HPP_INCLUDED
#define ODBCXX_SESSION_HPP_INCLUDED

#include "config.hpp"

namespace odbcxx {

	class connection;
	class statement;
    /**
     * Standards for an opened connection.
     */
	class session {
		public:
			explicit session();
			~session();
            /**
             * Check whether this session object is valid.
             * @return true if this session object is valid, vice versa
             */
			operator bool() const;
            /**
             * Close this opened connection.
             * @return current instance.
             */
			session& close();

            /**
             * Retreive the connection string.
             * @return connection string.
             */
			inline SQLCHAR const* connstr() const
			{ return &m_buf[0]; }

            /**
             * Allocate the next level handle.
             * @param stmt the odbc statement handle.
             * @return the same as the input argument.
             */
			statement& alloc(statement &stmt);
		private:
            /**
             * The connection object initialized this session object.
             */
			connection *m_conn_ptr;
            /**
             * The output connection string generated by connect methods in
             * connection object. It is not the same as the input connection
             * string, as connect methods will filling other fields, it's
             * usually longer than the input one.
             */
			SQLCHAR m_buf[0x1 << 10];

			friend class connection;
			friend class statement;
	};

}

#endif //ODBCXX_SESSION_HPP_INCLUDED
