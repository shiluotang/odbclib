#ifndef ODBCXX_ENVIRONMENT_HPP_INCLUDED
#define ODBCXX_ENVIRONMENT_HPP_INCLUDED

#include "handle_object.hpp"

namespace odbcxx {

	class connection;
	class environment : public handle_object {
		public:
			enum version { 
				OV2 = SQL_OV_ODBC2, 
				OV3 = SQL_OV_ODBC2 
			};
		public:
			environment(version = OV3);
			void set_version(version) const;
			virtual ~environment() {}

			connection& alloc(connection&);

			friend class connection;
	};

}

#endif //ODBCXX_ENVIRONMENT_HPP_INCLUDED
