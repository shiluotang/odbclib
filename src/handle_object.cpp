#include "handle_object.hpp"

using namespace std;

namespace odbcxx {

	handle_object::handle_object(handle const& h) :m_handle(h) {}

	handle_object::~handle_object() {
		if(m_handle != handle::null) {
			m_handle.close();
			m_handle = handle::null;
		}
	}

	bool handle_object::close_handle() {
		if(SQL_SUCCEEDED(m_handle.close())) {
			m_handle = handle::null;
			return true;
		}
		return false;
	}
}
