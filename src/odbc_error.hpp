#ifndef ODBCLIB_ODBC_ERROR_HPP_INCLUDED
#define ODBCLIB_ODBC_ERROR_HPP_INCLUDED

#include <stdexcept>

namespace odbcxx {

	class handle;
	class odbc_error : public std::runtime_error {
		public:
			explicit odbc_error(std::string const&);
			explicit odbc_error(handle const&);
	};

}

#endif //ODBCLIB_ODBC_ERROR_HPP_INCLUDED
