#include "Event.h"

Event::Event()
{
	Execute = [] (void) {
		Logger::Log(Logger::WARNING, "Execute function not set. Please set an execute function for this event");
	};
}

Event::Event(void (*Execute)())
{
	this->Execute = Execute;
}

Event::Event(const Event &e)
{
	this->Execute = e.Execute;
}