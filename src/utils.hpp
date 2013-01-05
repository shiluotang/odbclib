#ifndef ODBCXX_UTILS_HPP_INCLUDED
#define ODBCXX_UTILS_HPP_INCLUDED

#include <cstddef>

template<typename T, std::size_t N>
std::size_t countof(T const (&a)[N]) { return N;}

#endif //ODBCXX_UTILS_HPP_INCLUDED
