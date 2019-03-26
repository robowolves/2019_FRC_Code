#pragma once

#include <memory>
#include <iterator>
#include <vector>
#include <string>

#include <frc/RobotDrive.h>
#include "ctre/Phoenix.h"

#include "FRCLogger.h"

#include "Constants.h"
using namespace RobotConstants::DriveTrain;

class DriveTrain
{
public:
	DriveTrain(std::vector<int>, std::shared_ptr<FRCLogger>& logger);
	~DriveTrain();

	void setDriveOption(driveOptions); //Sets the drive train option.
	driveOptions getCurrentDriveOption();

	void setDrivePower(double, double); //Drives the robot based on current drive config. (Left value, Right value).

	const std::vector< std::shared_ptr<WPI_TalonSRX> >& getTalonControllers(); //Returns controllers so that other classes (debug) can get information.
	
private:
	std::vector< std::shared_ptr<WPI_TalonSRX> > talonSRXControllers;

	std::unique_ptr<frc::RobotDrive> driveTrain;

	driveOptions currentDriveOption;

	std::shared_ptr<FRCLogger> driveLogger;
};