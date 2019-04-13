#ifndef JOB_OBJECT_H_
#define JOB_OBJECT_H_

struct JobObject
{
	char value;

	JobObject() : value('!') {}
	JobObject(char val) : value(val) {}
};

#endif
