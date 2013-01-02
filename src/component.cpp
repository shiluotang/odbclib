#include "component.hpp"

#include <iostream>

using namespace std;
using namespace odbclib::handle;

NS_BEGIN_1(odbclib)

Component::Component()
	:m_has_tried_dispose(false),
	m_disposed(false)
{
	DEBUG_INIT("Component");
}

Component::~Component()
{
	DEBUG_RELEASE("Component");
}

void
Component::dispose()
{
	if(m_disposed)
		return;
	m_has_tried_dispose = true;
	onDisposing();
	doDispose();
	m_disposed = true;
	onDisposed();
}

void Component::onDisposing(){m_disposingEvent.occur(DisposeEventArgs(*this));}
void Component::onDisposed(){m_disposedEvent.occur(DisposeEventArgs(*this));}

void
Component::onEvent(DisposeEvent & event,
		DisposeEventArgs const& args)
{
	dispose();
}

NS_END_1
