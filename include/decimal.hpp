#ifndef ODBCLIB_DECIMAL_HPP_INCLUDED
#define ODBCLIB_DECIMAL_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

NS_BEGIN_1(odbclib)

class Decimal
{
	public:
	       	bool operator == (Decimal const& )const;
		inline bool operator != (Decimal const& other)const{return !(*this == other);}
		inline bool operator >= (Decimal const& other)const{return !(*this < other);}
		inline bool operator > 	(Decimal const& other)const{return other < *this;}
		inline bool operator <=	(Decimal const& other)const{return *this < other || *this == other;}
		bool operator <	(Decimal const& )const;
};

NS_END_1

#endif //ODBCLIB_DECIMAL_HPP_INCLUDED
