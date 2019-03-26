#pragma once

#include <memory>
#include <string>
#include <cmath>

#include <frc/DriverStation.h>
#include <frc/Joystick.h>

#include "FRCLogger.h"

#include "Constants.h"
using namespace RobotConstants::HID;

class HID
{
public:
	HID(frc::DriverStation&, std::shared_ptr<FRCLogger>&);
	~HID();

	double getRawAxis(controllerMappingName);
	double getAdjustedAxis(controllerMappingName);

	bool getButtonPressed(controllerMappingName);

private:
	std::unique_ptr<frc::Joystick> driverController = std::make_unique<frc::Joystick>(0); //The first connected controller the driver station detects.
	std::string currentControllerName;

	std::shared_ptr<FRCLogger> HIDLogger;
};

