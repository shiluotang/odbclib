#ifndef ODBCLIB_DISPOSEEVENTARGS_HPP_INCLUDED
#define ODBCLIB_DISPOSEEVENTARGS_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"

NS_BEGIN_1(odbclib)

class Disposable;
class DisposeEventArgs
{
public:
	DisposeEventArgs(Disposable& disposable)
		:m_disposable(disposable)
	{}
	inline Disposable &
	getDisposable() const
	{return m_disposable;}
private:
	mutable Disposable &m_disposable;
};

NS_END_1

#endif //ODBCLIB_DISPOSEEVENTARGS_HPP_INCLUDED
