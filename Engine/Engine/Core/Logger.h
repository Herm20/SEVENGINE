#ifndef LOGGER_H_
#define LOGGER_H_

#include <boost/container/string.hpp>
#include <boost/chrono.hpp>
#include "Timer.h"

namespace Logger
{
	enum LogType { MSG, ERROR, WARNING };
	void Log(LogType type, const char* msg);
	const char* GetLog();
	boost::container::string GetFormatedSystemTime();
};

#endif