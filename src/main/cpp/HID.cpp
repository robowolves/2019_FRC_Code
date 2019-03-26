#include "HID.h"



HID::HID(frc::DriverStation& ds, std::shared_ptr<FRCLogger>& logger)
{
	//Get the name of the first controller detected, if it doesn't match the controller config it throws an out_of_range exception
	//and sets the temporary mapping of the unknown controller to the mapping of the Logitech Dual Action controller.
	logger->postMessage(RobotConstants::FRCLogger::logType::Info, "Initializing HID Class");
	logger->postMessage(RobotConstants::FRCLogger::logType::Verbose, 1, "Getting controller mapping");
	try 
	{
		std::string tmpControllerName = ds.GetJoystickName(0);
		controllerMapping.at(tmpControllerName); //Will generate OOR exception.

		currentControllerName = tmpControllerName;
		logger->postMessage(RobotConstants::FRCLogger::logType::Verbose, 2, "Found valid configuration: " + currentControllerName);
	}
	catch (const std::out_of_range& err)
	{
		logger->postMessage(RobotConstants::FRCLogger::logType::Severe, 2, "Unknown Controller Inserted (" + ds.GetJoystickName(0) + ")! Reverting to the default mapping (" + defaultControllerMapping+ ") [" + static_cast<std::string>(err.what()) + "]");
		currentControllerName = defaultControllerMapping;
	}
	HIDLogger = logger;
}


HID::~HID()
{
}

double HID::getRawAxis(controllerMappingName axisName)
{
	try
	{
		int axisID = controllerMapping.at(currentControllerName).at(axisName); //Looks up the axis/port number for the controller from the mapping.

		return driverController->GetRawAxis(axisID);
	}
	catch (const std::out_of_range& err)
	{
		HIDLogger->postMessage(RobotConstants::FRCLogger::logType::Severe, "Bad attempt to get raw axis value (Lookup key: " + std::to_string(static_cast<int>(axisName)) + ") [" + static_cast<std::string>(err.what()) + "]");
		return 0;
	}
}

double HID::getAdjustedAxis(controllerMappingName axisName)
{
	try
	{
		int axisID = controllerMapping.at(currentControllerName).at(axisName); //Looks up the axis/port number for the controller from the mapping.

		double value = driverController->GetRawAxis(axisID);

		if (value > RobotConstants::HID::joystickDeadband || value < -1 * RobotConstants::HID::joystickDeadband) //Adjusts for deadband.
		{
			//Value does not change.
		}
		else
			value = 0;

		value = RobotConstants::HID::joystickSensitivityCoefficent * std::pow(value, 3) + (1 - RobotConstants::HID::joystickSensitivityCoefficent) * value; //Adjusts for sensitivity constant. Thanks Nick, this was the only usefull contribution to the robot, your legacy will live on.

		return value;
	}
	catch (const std::out_of_range& err)
	{
		HIDLogger->postMessage(RobotConstants::FRCLogger::logType::Severe, "Bad attempt to get raw adjusted axis value (Lookup key: " + std::to_string(static_cast<int>(axisName)) + ") [" + static_cast<std::string>(err.what()) + "]");
		return 0;
	}
}

bool HID::getButtonPressed(controllerMappingName buttonName)
{
	try
	{
		int buttonID = controllerMapping.at(currentControllerName).at(buttonName); //Looks up the button number for the controller from the mapping.
		return driverController->GetRawButtonPressed(buttonID);
	}
	catch (const std::out_of_range& err)
	{
		HIDLogger->postMessage(RobotConstants::FRCLogger::logType::Severe, "Bad attempt to get button value (Lookup key: " + std::to_string(static_cast<int>(buttonName)) + ") [" + static_cast<std::string>(err.what()) + "]");
		return false;
	}
}
