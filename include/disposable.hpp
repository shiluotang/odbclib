#ifndef ODBCLIB_DISPOSABLE_HPP_INCLUDED
#define ODBCLIB_DISPOSABLE_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "utils/event/event.hpp"
#include "utils/event/eventlistener.hpp"
#include "disposeeventargs.hpp"

NS_BEGIN_1(odbclib)

class DisposeEventArgs;
class Disposable
{
	public:
		typedef odbclib::utils::event::Event<DisposeEventArgs> DisposeEvent;
		typedef odbclib::utils::event::EventListener<DisposeEventArgs> DisposeListener;
	public:
		virtual void dispose() = 0;
};

NS_END_1

#endif
