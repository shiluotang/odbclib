#include "buffer.hpp"
#include <cstring>
#include <utility>

using namespace std;

namespace odbcxx {
	buffer::buffer(size_t n) :_M_addr(0), _M_size(0) {
		if (n > 0) {
			_M_addr = new char[n];
			_M_size = n;
		}
	}
	buffer::buffer(buffer const &other) :_M_addr(0), _M_size(0) {
		if (other._M_size > 0) {
			_M_addr = new char[other._M_size];
			_M_size = other._M_size;
			std::memcpy(_M_addr, other._M_addr, other._M_size);
		}
	}
	buffer::buffer(buffer &&other) noexcept
		:_M_addr(other._M_addr),
		_M_size(other._M_size) {
		other._M_addr = 0;
		other._M_size = 0;
	}
	buffer::~buffer() {
		if (_M_addr) {
			delete[] _M_addr;
			_M_addr = 0;
			_M_size = 0;
		}
	}

	buffer& buffer::operator = (buffer const &other) {
		if (_M_size != other._M_size) {
			if (other._M_size > 0) {
				char *old_mem = _M_addr;
				char *new_mem = new char[other._M_size];
				std::memcpy(new_mem, other._M_addr, other._M_size);
				_M_size = other._M_size;
				_M_addr = new_mem;
				if (old_mem)
					delete[] old_mem;
			} else {
				if (_M_addr)
					delete[] _M_addr;
				_M_addr = 0;
				_M_size = 0;
			}
		} else if (this != &other)
			std::memcpy(_M_addr, other._M_addr, other._M_size);
		return *this;
	}
	buffer& buffer::operator = (buffer &&other) noexcept {
		std::swap(_M_addr, other._M_addr);
		std::swap(_M_size, other._M_size);
		return *this;
	}

	buffer& buffer::resize(std::size_t n) {
		if (n == _M_size)
			return *this;
		char *old_addr = _M_addr;
		char *new_addr = n > 0 ? new char[n] : 0;
		_M_addr = new_addr;
		_M_size = n;
		if (old_addr)
			delete[] old_addr;
		return *this;
	}
}
