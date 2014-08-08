#ifndef ODBCXX_HANDLE_OBJECT_HPP_INCLUDED
#define ODBCXX_HANDLE_OBJECT_HPP_INCLUDED

#include "handle.hpp"

namespace odbcxx {

    /**
     * This class contains a odbc handle in it.
     */
	class handle_object {
		public:
            /**
             * Check whether the odbc handle of this object is valid.
             * @return true if handle is valid, vice versa.
             */
			inline operator bool() const
			{ return static_cast<bool>(_M_handle); }
            /**
             * Close the odbc handle of this object.
             * @return true if handle before close is valid, vice versa.
             */
			bool close_handle();
		protected:
            /**
             * Construct handle_object based on the specified odbc handle.
             * @param h the specified odbc handle.
             */
			explicit handle_object(handle const &h = handle::null);
			virtual ~handle_object();

            /**
             * The handle object inside this object.
             */
			handle _M_handle;
	};
}

#endif //ODBCXX_HANDLE_OBJECT_HPP_INCLUDED
