#ifndef EVENT_H_
#define EVENT_H_

#include "Logger.h"

class Event
{
public:
	Event();
	Event(void (*Exectute)());
	Event(const Event &e);

	void (*Execute)(void) = nullptr;
};

#endif
