#ifndef ODBCXX_DIAGINFO_HPP_INCLUDED
#define ODBCXX_DIAGINFO_HPP_INCLUDED

#include "config.hpp"
#include <string>

namespace odbcxx {

    /**
     * Diagnostic information.
     */
	struct diaginfo {
        /**
         * odbc state code.
         */
		SQLCHAR _M_state[7];
		/**
		 * native error code.
		 */
		SQLINTEGER _M_native_error_code;
        /**
         * odbc error message.
         */
		std::string _M_message;
	};

	std::ostream& operator << (std::ostream&, diaginfo const&);
}

#endif //ODBCXX_DIAGINFO_HPP_INCLUDED
