#pragma once
#include <string>
#include <map>
#include <vector>

namespace RobotConstants {
	namespace DriveTrain {
		enum class driveOptions : char { TankDrive = 'T', ArcadeDrive = 'A' };

		const std::vector<int> talonSRXCANIDs = {
			2 /*Left Front*/, 4 /*Left Back*/, 1 /*Right Front*/, 3 /*Right Back*/
		};
	}
	namespace HID {

		const double joystickDeadband = 0.05; //5% Dead band.

		const double joystickSensitivityCoefficent = 0.02; //Note: The higher the value the more exponential the sensitivity appears to becomes,
														   //	   (up to jsc = 1, past this the graph dips down and becomes negitive [the robot will drive backwards]).

		//Note: An enum class for referencing axis/button names can be used to save memory, and to reduce programming errors at runtime, but looses the ability to see what key is being referenced.
		enum class controllerMappingName : int {
			leftJoystickXAxis = 1,
			leftJoystickYAxis = 2,
			rightJoystickXAxis = 3,
			rightJoystickYAxis = 4,
			xButton = 5,
			yButton = 6,
			aButton = 7,
			upButton = 8,
			downButton = 9,
			leftButton = 10,
			rightButton = 11,
			leftShoulder = 12,
			lzShoulder = 13,
			rightShoulder = 14,
			rzShoulder = 15,
			startButton = 16,
			selectButton = 17
		};

		//Note: These values are determined by values manually obtained on the Driver Station, 
		//      if another controller is used each value must be determined for the new controller.
		const std::map< std::string, std::map<controllerMappingName, int> > controllerMapping = {
			{"Logitech Dual Action", {
					{controllerMappingName::leftJoystickXAxis, 0},
					{controllerMappingName::leftJoystickYAxis, 1},
					{controllerMappingName::rightJoystickXAxis, 2},
					{controllerMappingName::rightJoystickYAxis, 3},
					{controllerMappingName::selectButton, 10} }
			},
			{"Logitech RumblePad 2 USB", {
					{controllerMappingName::leftJoystickXAxis, 0},
					{controllerMappingName::leftJoystickYAxis, 1},
					{controllerMappingName::rightJoystickXAxis, 2},
					{controllerMappingName::rightJoystickYAxis, 3},
					{controllerMappingName::selectButton, 10} }
			},
		};

		const std::string defaultControllerMapping = "Logitech Dual Action";
	}
	namespace FRCLogger {
		enum class logType : char { Verbose = 'V', Info = 'I', Warning = 'W', Severe = 'S', Fatal = 'F' };

		const std::string logFilePath = "";
	}
}