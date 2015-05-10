#include "handle_object.hpp"

using namespace std;

namespace odbcxx {

	handle_object::handle_object(handle const& h) :_M_handle(h) {}

	handle_object::~handle_object() {
		close_handle();
	}

	void handle_object::close_handle() {
		if(_M_handle)
			_M_handle.close();
	}
}
