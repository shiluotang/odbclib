#include "eventlistener.hdr.tcc"
#include <algorithm>

namespace odbclib
{
	namespace utils
	{
		namespace event
		{

			template<typename T>
			Event<T>::~Event()
			{
				removeListeners();
			}
			
			template<typename T>
			Event<T> & Event<T>::addListener(EventListener<T> &listener)
			{ 
				m_listeners.push_back(&listener);
				listener.m_events.push_back(this);
				return *this;
			}
			
			template<typename T>
			Event<T> & Event<T>::removeListener(EventListener<T> &listener)
			{
				m_listeners.erase(
					std::remove(
						m_listeners.begin(),
						m_listeners.end(),
						&listener),
					m_listeners.end());
				listener.m_events.erase(
					std::remove(
						listener.m_events.begin(),
						listener.m_events.end(),
						this),
					listener.m_events.end());
				return *this;
			}
			
			template<typename T>
			Event<T> & Event<T>::removeListeners()
			{
				ListenerList listeners(m_listeners);
				for(typename ListenerList::iterator iter = listeners.begin();
					iter != listeners.end(); ++iter)
					(*iter)->m_events.erase(
						std::remove(
							(*iter)->m_events.begin(),
							(*iter)->m_events.end(),
							this),
						(*iter)->m_events.end());	
				m_listeners.clear();
				return *this;
			}
			
			template<typename T>
			void Event<T>::notifyListeners(T const& e)
			{
				ListenerList listeners(m_listeners);
				for(typename ListenerList::iterator iter = listeners.begin();
					iter != listeners.end(); ++iter)
					(*iter)->onEvent(*this,e);
			}

			template<typename T>
			void Event<T>::occur(T const& e)
			{notifyListeners(e);}
		}
	}
}
