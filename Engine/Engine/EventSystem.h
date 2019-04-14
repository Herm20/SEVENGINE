#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include <list>
#include <map>
using std::multimap;
using std::list;
using std::pair;

#include "Listener.h"

class EventSystem
{
private: 
	// Database of Clients & their events
	multimap<EVENTID, Listener*> database;

	// List of events to be processed
	list<Event> currentEvents;

	// Helper Methods
	bool AlreadyRegistered(EVENTID eventId, Listener* client);
	void DispatchEvent(Event* _event);


	// Singleton, deny access to consturctor/destructors
	EventSystem();
	~EventSystem();
	EventSystem(const EventSystem& rhs);
	//EventSystem& operator=(const EventSystem& rhs);
public:
	// Returns an instance of the Event System
	static EventSystem* Instance();

	// Registers a client to start istening for an event
	void RegisterClient(EVENTID event, Listener* client);

	// Unregisters a client from a specific event
	void UnregisterClient(EVENTID event, Listener* client);

	// Unregister a client from all events
	void UnregisterAll(Listener* client);

	// Send an event
	void SendEvent(EVENTID eventId, void* data);

	// Process all events
	void ProcessEvents();

	void ClearEvents();

	// Shutdown EventSystem
	void ShutDown();
};
#endif // EVENTSYSTEM_H_

