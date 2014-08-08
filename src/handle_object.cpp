#include "handle_object.hpp"

using namespace std;

namespace odbcxx {

	handle_object::handle_object(handle const& h) :_M_handle(h) {}

	handle_object::~handle_object() {
		if(_M_handle != handle::null) {
			_M_handle.close();
			_M_handle = handle::null;
		}
	}

	bool handle_object::close_handle() {
		if(SQL_SUCCEEDED(_M_handle.close())) {
			_M_handle = handle::null;
			return true;
		}
		return false;
	}
}
