#include "Logger.h"

namespace Logger
{
	static std::string logTxt;
	static struct tm* timeinfo;
	static std::time_t systemtime;
}

/*! \brief Generates a log in the logfile
 *
 * \param (LogType) type - The type of message to log
 * \param (const char*) msg - The message to log
 */
void Logger::Log(LogType type, const char* msg)
{
	logTxt += GetFormatedSystemTime();

	switch(type)
	{
		case LogType::ERROR:
			logTxt += "  :  ERR  :  ";
			break;
		case LogType::WARNING:
			logTxt += "  :  WRN  :  ";
			break;
		case LogType::MSG:
		default:
			logTxt += "  : MSG :  ";
			break;
	}

	logTxt += msg;
	logTxt += "\n";
}

/*! \brief Gets the log
 *
 * \return (const char*) The log
 */
const char* Logger::GetLog()
{
	return logTxt.c_str();
}

/*! \brief Gets the date and time formatted in iso 8601
 *
 * \return (std::string) The formatted time
 */
std::string Logger::GetFormatedSystemTime()
{
	systemtime = boost::chrono::system_clock::to_time_t(boost::chrono::system_clock::now());
	timeinfo = std::localtime(&systemtime);
	char timeStr[20];
	strftime(timeStr, 20, "%F %T", timeinfo);
	return std::string(timeStr);
}