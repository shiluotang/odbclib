#include "event.hdr.tcc"
#include <algorithm>

namespace odbclib
{
	namespace utils 
	{
		namespace event
		{
			template<typename T>
			EventListener<T>::~EventListener()
			{
				EventList events(m_events);
				for(typename EventList::iterator iter = events.begin();
					iter != events.end(); ++iter)
					(*iter)->removeListener(*this);
			}
			
			template<typename T>
			void EventListener<T>::onEvent(Event<T> &e, T const& arg)
			{
				
			}
		}
	}
}
