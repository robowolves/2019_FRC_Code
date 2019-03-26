#include "DriveTrain.h"


/*
 * DriveTrain([frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor]) 
 */
DriveTrain::DriveTrain(std::vector<int> talonIDs, std::shared_ptr<FRCLogger>& logger)
{
	logger->postMessage(RobotConstants::FRCLogger::logType::Info, "Initializing DriveTrain Class");
	logger->postMessage(RobotConstants::FRCLogger::logType::Verbose, 1, "Initializing " + std::to_string(talonIDs.size()) + " Talons");
	for (auto Iter : talonIDs) //Initialize Talons to the ID's in the talonIDs range.
	{
		talonSRXControllers.push_back (std::make_shared<WPI_TalonSRX>(Iter) );
		talonSRXControllers.back()->SetSafetyEnabled(true); //This prevents the robot from hurting itself or others if the code locks up or the actuator does not update.
		talonSRXControllers.back()->Set(ControlMode::PercentOutput, 0); //Resets the motor safety timeout.
	}

	if (talonSRXControllers.size() == 4) 
	{
		talonSRXControllers.at(0)->SetInverted(true); //Set the left-hand-side motors to be inverted compared to the left-hand-side..
		talonSRXControllers.at(1)->SetInverted(true); //..This way the robot will drive forward correctly.

		talonSRXControllers.at(2)->SetInverted(true); //Set the right-hand-side motors to be inverted compared to the left-hand-side..
		talonSRXControllers.at(3)->SetInverted(true); //..This way the robot will drive forward correctly.

		driveTrain = std::make_unique<frc::RobotDrive>(talonSRXControllers.at(0), talonSRXControllers.at(1), talonSRXControllers.at(2), talonSRXControllers.at(3));
	}
	else 
	{
		talonSRXControllers.at(1)->SetInverted(true); 
		driveTrain = std::make_unique<frc::RobotDrive>(talonSRXControllers.at(0), talonSRXControllers.at(1));
	}
	
	currentDriveOption = driveOptions::TankDrive; //Default value, operator can change later (Or ingame).
	logger->postMessage(RobotConstants::FRCLogger::logType::Info, 1, "Current drive scheme: " + static_cast<char> (getCurrentDriveOption()));

	driveLogger = logger;	
}

DriveTrain::~DriveTrain()
{
}

void DriveTrain::setDriveOption(driveOptions newSelection)
{
	driveLogger->postMessage( RobotConstants::FRCLogger::logType::Info, "Switched drive mode to: " + static_cast<char> (getCurrentDriveOption()) );
	currentDriveOption = newSelection;
}

driveOptions DriveTrain::getCurrentDriveOption()
{
	return currentDriveOption;
}

void DriveTrain::setDrivePower(double leftJoyValue, double rightJoyValue)
{
	if (currentDriveOption == driveOptions::TankDrive)
	{
		driveTrain->TankDrive(leftJoyValue, rightJoyValue);
	}
	else
	{
		driveTrain->ArcadeDrive(leftJoyValue, rightJoyValue); //Uses Arcade Drive. (Forward/Back movement value, Rotation value).
	}
}

const std::vector<std::shared_ptr<WPI_TalonSRX>>& DriveTrain::getTalonControllers()
{
	return talonSRXControllers;
}
