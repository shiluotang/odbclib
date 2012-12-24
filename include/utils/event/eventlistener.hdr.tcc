#ifndef EVENTLISTENER_HDR_TCC_INCLUDED
#define EVENTLISTENER_HDR_TCC_INCLUDED

#include <vector>

namespace odbclib
{
	namespace utils 
	{
		namespace event
		{
			template<typename T> class Event;
			
			template<typename EventArgType>
			class EventListener
			{
			public:
				typedef std::vector< Event<EventArgType>* > EventList;
			
				virtual ~EventListener();
				virtual void onEvent(Event<EventArgType> &,EventArgType const&);
			
			private:
				EventList m_events;
			
				friend class Event<EventArgType>;
			};

		}
	}
}

#endif
