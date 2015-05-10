#ifndef ODBCXX_HANDLE_OBJECT_HPP_INCLUDED
#define ODBCXX_HANDLE_OBJECT_HPP_INCLUDED

#include "handle.hpp"

namespace odbcxx {

    /**
     * This class contains an odbc handle in it.
     */
	class handle_object {
		public:
			operator bool() const { return _M_handle; }
			void close_handle();
		protected:
			explicit handle_object(handle const& = handle::null);
			virtual ~handle_object();
		protected:
			handle _M_handle;
	};
}

#endif //ODBCXX_HANDLE_OBJECT_HPP_INCLUDED
