#include "EventSystem.h"

// Returns an instance of the Event System
EventSystem * EventSystem::Instance()
{
	static EventSystem instance;
	return &instance;
}

bool EventSystem::AlreadyRegistered(EVENTID eventId, Listener * client)
{
	// Assume they are not already registered
	bool alreadyRegistered = false;

	// Range Iterator
	pair<multimap<EVENTID, Listener*>::iterator,
		multimap<EVENTID, Listener*>::iterator> range;

	// Find all the clients able to recieve this event
	range = database.equal_range(eventId);

	// Go through list of clients
	for (multimap<EVENTID, Listener*>::iterator iter = range.first; iter != range.second; iter++) 
	{
		// If this client is already subscribed
		if ((*iter).second == client) 
		{
			// Subscribe then quit
			alreadyRegistered = true;
			break;
		}
	}

	return alreadyRegistered;
}

void EventSystem::DispatchEvent(Event * _event)
{
	// Iterator needed
	pair<multimap<EVENTID, Listener*>::iterator,
		multimap<EVENTID, Listener*>::iterator> range;

	// Get all the clients who respond to this event
	range = database.equal_range(_event->EventId());

	// For every client
	for (multimap<EVENTID, Listener*>::iterator iter = range.first; iter != range.second; iter++) 
	{
		// Handle the event
		(*iter).second->HandleEvent(_event);
	}

}

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
	this->ShutDown();
}

// Registers a client to start istening for an event
void EventSystem::RegisterClient(EVENTID event, Listener * client)
{
	// If the client is null, or already registered
	if (!client || AlreadyRegistered(event, client)) 
	{
		// Quit now
		return;
	}

	// Insert the client into the database
	database.insert(make_pair(event, client));
}

// Unregisters a client from a specific event
void EventSystem::UnregisterClient(EVENTID event, Listener * client)
{
	// Iterator needed
	pair<multimap<EVENTID, Listener*>::iterator,
		multimap<EVENTID, Listener*>::iterator> range;

	// Find all the client able to recieve this event
	range = database.equal_range(event);

	for (multimap<EVENTID, Listener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		// If this is the event we want to remove
		if ((*iter).second == client) 
		{
			// Erase the event then quit
			iter = database.erase(iter);
			break;
		}
	}
}

// Unregister a client from all events
void EventSystem::UnregisterAll(Listener * client)
{
	// Iterator needed
	multimap<EVENTID, Listener*>::iterator iter = database.begin();

	// For every entry in the database
	while (iter != database.end()) 
	{
		// If this is the client we want
		if ((*iter).second == client) 
		{
			// Erase it from the database
			iter = database.erase(iter);
		}
		else 
		{
			// Keep moving 
			iter++;
		}
	}
}

// Send an event
void EventSystem::SendEvent(EVENTID eventId, void * data)
{
	// Create the new event
	Event newEvent(eventId, data);
	// Queue it up
	currentEvents.push_back(newEvent);
}

// Process all events
void EventSystem::ProcessEvents()
{
	// For every event
	while (currentEvents.size()) 
	{
		// Dispatch the event
		DispatchEvent(&currentEvents.front());
		// Remove it from the list
		currentEvents.pop_front();
	}
}

void EventSystem::ClearEvents()
{
	// Clear all of our events
	currentEvents.clear();
}

// Shutdown EventSystem
void EventSystem::ShutDown()
{
	database.clear();
	currentEvents.clear();
}
