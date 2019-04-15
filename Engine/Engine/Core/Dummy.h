#pragma once
#include "Listener.h"

class Dummy: public Listener
{
private:
	int id = 0;

public:
	Dummy(int _id);
	~Dummy();
	void HandleEvent(Event* _event);
};

