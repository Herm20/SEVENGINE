#ifndef EVENT_H_
#define EVENT_H_

#include <string>
using std::string;
#define EVENTID string

class Event
{
private:
	// Members
	EVENTID eventId;
	void* parameter;
public:
	Event(EVENTID eventId, void* parameter){
		this->eventId = eventId;
		this->parameter = parameter;
	}
	~Event() {};
	// Accessors
	inline EVENTID EventId() const { return eventId; }
	inline void* Parameter() { return parameter; }
};
#endif // EVENT_H_

