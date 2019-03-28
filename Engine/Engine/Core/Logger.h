#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <boost/chrono.hpp>
#include "Timer.h"

namespace Logger
{
	enum LogType { MSG, ERROR, WARNING };
	void Log(LogType type, const char* msg);
	const char* GetLog();
	std::string GetFormatedSystemTime();
};

#endif