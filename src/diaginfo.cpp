#include "diaginfo.hpp"
#include <ostream>

using namespace std;

namespace odbcxx {

	ostream& operator << (ostream &os, diaginfo const& di) {
		return os << "[" << di._M_state
			<< "]:[" << di._M_native_error_code
			<< "]:" << di._M_message;
	}

}
