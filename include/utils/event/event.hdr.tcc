#ifndef EVENT_HDR_TCC_INCLUDED
#define EVENT_HDR_TCC_INCLUDED

#include <vector>

namespace odbclib
{
	namespace utils 
	{
		namespace event
		{
			template <typename T> class EventListener;
			
			template<typename EventArgType>
			class Event
			{
			public:
				typedef std::vector< EventListener<EventArgType>* > ListenerList;
			public:
				virtual ~Event();
				virtual Event & addListener(EventListener<EventArgType> &);
				virtual Event & removeListener(EventListener<EventArgType> &);
				virtual Event & removeListeners();
				
				virtual void occur(EventArgType const&);				
				
				inline bool operator == (Event<EventArgType> const& other) const{return this == &other;}
				inline bool operator != (Event<EventArgType> const& other)const{return !(*this == other);}
			protected:
				virtual void notifyListeners(EventArgType const&);
			private:
				ListenerList m_listeners;
			};
		}
	}
}

#endif
