#ifndef LISTENER_H_
#define LISTENER_H_
#include "Event.h"

class Listener
{
public:
	Listener() {};
	virtual ~Listener() {};
	// Handles the event passed into it
	virtual void HandleEvent(Event * _event) {};
};
#endif // LISTENER_H_

