#include "odbc_error.hpp"
#include "handle.hpp"

#include <sstream>
#include <string>

using namespace std;

namespace {

	string dump_msg(odbcxx::handle const& hh) {
		odbcxx::diaginfo info;
		hh.diag(1, info);
		stringstream ss;
		ss << info;
		return ss.str();
	}
}

namespace odbcxx {

	odbc_error::odbc_error(string const &msg)
		:runtime_error(msg) {
	}

	odbc_error::odbc_error(handle const& h)
		:runtime_error(dump_msg(h)) {
	}


}
