#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <boost/chrono.hpp>
#include "Timer.h"

namespace Logger
{
	enum LOGTYPE { MSG, ERROR, WARNING };
	void Log(LOGTYPE type, const char* msg);
	const char* GetLog();
};

#endif