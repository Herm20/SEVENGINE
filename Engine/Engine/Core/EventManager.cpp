#include "EventManager.h"

boost::lockfree::queue<Event> EventManager::eventQueue{100};

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::QueueEvent(const Event &e)
{
	eventQueue.push(e);
}

void EventManager::ExecuteNext()
{
	if(!eventQueue.empty())
	{
		Event e;
		eventQueue.pop(e);
		e.Execute();
	}
}