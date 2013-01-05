#ifndef ODBCXX_DIAGINFO_HPP_INCLUDED
#define ODBCXX_DIAGINFO_HPP_INCLUDED

#include "config.hpp"
#include <iosfwd>

namespace odbcxx {

	struct diaginfo {
		SQLCHAR m_state[7];
		/**
		 * native error code
		 */
		SQLINTEGER m_nec;
		SQLCHAR m_msg[0x1 << 10];
	};

	std::ostream& operator << (std::ostream&, diaginfo const&);
}

#endif //ODBCXX_DIAGINFO_HPP_INCLUDED
