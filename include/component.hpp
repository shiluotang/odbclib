#ifndef ODBCLIB_COMPONENT_HPP_INCLUDED
#define ODBCLIB_COMPONENT_HPP_INCLUDED

#include "disposable.hpp"
#include "handle.hpp"

NS_BEGIN_1(odbclib)
class Component:
	public Disposable,
	public Disposable::DisposeListener
{
	public:
		Component();
		virtual ~Component();

		virtual void dispose();
		virtual void onDisposing();
		virtual void onDisposed();
		virtual void doDispose() = 0;

		inline void 
		addDisposingListener(DisposeListener &l)
		{m_disposingEvent.addListener(l);}
		inline void
		addDisposedListener(DisposeListener &l)
		{m_disposingEvent.addListener(l);}
		inline void
		removeDisposingListener(DisposeListener &l)
		{m_disposingEvent.removeListener(l);}
		inline void
		removeDisposedListener(DisposeListener &l)
		{m_disposedEvent.removeListener(l);}

		virtual void
		onEvent(DisposeEvent &,DisposeEventArgs const&);

	protected:
		bool m_has_tried_dispose;
		bool m_disposed;

		DisposeEvent m_disposingEvent;
		DisposeEvent m_disposedEvent;

		friend class Connection;
};

NS_END_1

#endif
