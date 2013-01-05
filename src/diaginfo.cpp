#include "diaginfo.hpp"
#include <ostream>

using namespace std;

namespace odbcxx {

	ostream& operator << (ostream &os, diaginfo const& di) {
		return os << "[" << di.m_state 
			<< "]:[" << di.m_nec
			<< "]:" << di.m_msg;
	}

}
