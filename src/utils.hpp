#ifndef ODBCXX_UTILS_HPP_INCLUDED
#define ODBCXX_UTILS_HPP_INCLUDED

#include <cstddef>
#include <sstream>
#include <utility>

namespace odbcxx {

template<typename T, std::size_t N>
std::size_t countof(T const (&a)[N]) { return N;}

template<typename U, typename V>
	U sstream_cast(V const &src) {
		U dest;
		std::stringstream ss;
		ss << src;
		ss >> dest;
		return std::move(dest);
	}

}

#endif //ODBCXX_UTILS_HPP_INCLUDED
