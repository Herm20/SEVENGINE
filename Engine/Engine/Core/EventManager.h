#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <boost/lockfree/queue.hpp>
#include "Event.h"
#include "Types.h"

class EventManager
{
private:
	static boost::lockfree::queue<Event> eventQueue;

public:
	EventManager();
	~EventManager();

	static void QueueEvent(const Event &e);
	static void ExecuteNext();
};

#endif
