#ifndef ODBCLIB_BUFFER_HPP_INCLUDED
#define ODBCLIB_BUFFER_HPP_INCLUDED

#include <cstddef>

namespace odbcxx {
	
	class buffer {
		public:
			explicit buffer(std::size_t);
			buffer(buffer const&);
			buffer(buffer&&) noexcept;
			~buffer();
			buffer& operator = (buffer const&);
			buffer& operator = (buffer&&) noexcept;

			buffer& resize(std::size_t);
			char* addr() const { return _M_addr; }
			std::size_t size() const { return _M_size; }
		private:
			char *_M_addr;
			std::size_t _M_size;
	};
}

#endif //ODBCLIB_BUFFER_HPP_INCLUDED
