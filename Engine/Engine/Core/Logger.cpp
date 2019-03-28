#include "Logger.h"

namespace Logger
{
	static std::string logTxt;
	static struct tm* timeinfo;
	static std::time_t systemtime;
}

void Logger::Log(LOGTYPE type, const char* msg)
{
	systemtime = boost::chrono::system_clock::to_time_t(boost::chrono::system_clock::now());
	timeinfo = std::localtime(&systemtime);
	char timeStr[20];
	strftime(timeStr, 20, "%F %T", timeinfo);
	logTxt.append(timeStr);

	switch(type)
	{
		case LOGTYPE::ERROR:
			logTxt.append("  :  ERR  :  ");
			break;
		case LOGTYPE::WARNING:
			logTxt.append("  :  WRN  :  ");
			break;
		case LOGTYPE::MSG:
		default:
			logTxt.append("  : MSG :  ");
			break;
	}

	logTxt.append(msg);
	logTxt.append("\n");
}

const char* Logger::GetLog()
{
	return logTxt.c_str();
}