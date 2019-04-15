#include "Dummy.h"



Dummy::Dummy(int _id)
{
	id = _id;
}


Dummy::~Dummy()
{
}

void Dummy::HandleEvent(Event * _event)
{
	printf("Dummy: %i has fired an event \n", id);
}
