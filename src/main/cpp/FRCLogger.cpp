#include "FRCLogger.h"



FRCLogger::FRCLogger(frc::DriverStation& ds)
{
	if (ds.IsFMSAttached())
	{
		isCompetitionModeEnabled = true; //Reduces debugging output (ex. Do not file log or display verbose output).
	}
	postMessage(logType::Info, "Initalizing Logger");
	postMessage(logType::Info, 1, "Competition mode: " + std::to_string(isCompetitionModeEnabled));
	postMessage(logType::Info, 1, "Current robot time: " + getCurrentTime());
}

FRCLogger::FRCLogger(frc::DriverStation& ds, std::string logFile)
{
	if (ds.IsFMSAttached())
	{
		isCompetitionModeEnabled = true;
	}

	if (logFile.length() != 0) //No file path, (but a placeholder for a varable that can be changed in the constants).
	{
		logFilePath = logFile;
		isFileLoggingEnabled = true;
	}
	postMessage(logType::Info, "Initalizing Logger");
	postMessage(logType::Info, 1, "Competition mode: " + std::to_string(isCompetitionModeEnabled));
	postMessage(logType::Info, 1, "Log file path: "  + logFile);
	postMessage(logType::Info, 1, "Current robot time: " + getCurrentTime());
}

FRCLogger::~FRCLogger()
{
}

void FRCLogger::postMessage(logType messageSeverity, std::string msg)
{
	if (isCompetitionModeEnabled)
	{
		if (messageSeverity == logType::Verbose || messageSeverity == logType::Warning) return;
	}
	
	std::cout << static_cast<char>(messageSeverity) + " " + getCurrentTime() << ']' << ' ' << msg << '.' << '\n';
}

void FRCLogger::postMessage(logType messageSeverity, int indent, std::string msg)
{
	if (isCompetitionModeEnabled)
	{
		if (messageSeverity == logType::Verbose || messageSeverity == logType::Warning) return;
	}
	
	char indentSymbol = '>';
	if (messageSeverity == logType::Severe || messageSeverity == logType::Fatal)
		indentSymbol = '~';
	
	std::cout << static_cast<char>(messageSeverity) + " " + getCurrentTime() << ']' << "  " << std::string(indent - 1, ' ') << indentSymbol << msg << '.' << '\n';
}

void FRCLogger::enableFileLogging(bool enableDisableFlag)
{
	isFileLoggingEnabled = enableDisableFlag;
}

bool FRCLogger::getIsFileLogging()
{
	return isFileLoggingEnabled;
}

void FRCLogger::overideCompetitionMode(bool isCompModeFlag)
{
	isCompetitionModeEnabled = isCompModeFlag;
}

bool FRCLogger::getIsInCompetitionMode()
{
	return isCompetitionModeEnabled;
}

std::string FRCLogger::getCurrentTime()
{
	timeMutex.lock();
	std::time_t tt = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());
	std::string s =  static_cast<std::string> ( ctime(&tt) ); //ctime() is NOT thread safe! Keep this in mind, we'll need to find a thread-safe alternative in the future (but this shouldn't be a problem if only one instance of the logger class is used).
	timeMutex.unlock();										  //Using a Mutex provide a naive fail-safe approach for now in case it is accedentally used in a multi-threaded way.

	return s;
}