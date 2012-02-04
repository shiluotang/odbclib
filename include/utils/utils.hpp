#ifndef ODBCLIB_UTILS_HPP_INCLUDED
#define ODBCLIB_UTILS_HPP_INCLUDED

#include <sstream>

template<typename T>
std::string to_string(T value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

#endif //ODBCLIB_UTILS_HPP_INCLUDED
