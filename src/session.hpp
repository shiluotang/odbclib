#ifndef ODBCXX_SESSION_HPP_INCLUDED
#define ODBCXX_SESSION_HPP_INCLUDED

#include "config.hpp"

namespace odbcxx {

	class connection;
	class statement;
	class session {
		public:
			explicit session();
			~session();
			operator bool() const;
			session& close();

			inline SQLCHAR const* connstr() const
			{ return &m_buf[0]; }

			statement& alloc(statement&);
		private:
			connection *m_conn_ptr;
			SQLCHAR m_buf[0x1 << 10];

			friend class connection;
			friend class statement;
	};

}

#endif //ODBCXX_SESSION_HPP_INCLUDED
