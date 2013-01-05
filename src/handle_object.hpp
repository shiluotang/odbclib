#ifndef ODBCXX_HANDLE_OBJECT_HPP_INCLUDED
#define ODBCXX_HANDLE_OBJECT_HPP_INCLUDED

#include "handle.hpp"

namespace odbcxx {
	
	class handle_object {
		public:
			inline operator bool() const 
			{ return static_cast<bool>(m_handle); }
			bool close_handle();
		protected:
			explicit handle_object(handle const& = handle::null);
			virtual ~handle_object();

			handle m_handle;
	};
}

#endif //ODBCXX_HANDLE_OBJECT_HPP_INCLUDED
