#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <ctime>
#include <chrono>
#include <mutex> 

#include <frc/DriverStation.h>

#include "Constants.h"
using namespace RobotConstants::FRCLogger;

class FRCLogger
{
public:
	FRCLogger(frc::DriverStation&);
	FRCLogger(frc::DriverStation&, std::string);

	~FRCLogger();

	virtual void postMessage(logType, std::string);
	virtual void postMessage(logType, int, std::string);

	void enableFileLogging(bool);
	bool getIsFileLogging();

	void overideCompetitionMode(bool);
	bool getIsInCompetitionMode();
private:
	std::string getCurrentTime();
protected:
	bool isFileLoggingEnabled = false;
	std::string logFilePath = "";
	
	bool isCompetitionModeEnabled = false;

	std::mutex timeMutex;
};

