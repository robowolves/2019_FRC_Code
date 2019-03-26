/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_logger = std::make_shared<FRCLogger>(m_driverStation, RobotConstants::FRCLogger::logFilePath);
  m_HID = std::make_unique<HID>(m_driverStation, m_logger);
  m_driveTrain = std::make_unique<DriveTrain>(RobotConstants::DriveTrain::talonSRXCANIDs, m_logger);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  m_logger->postMessage(RobotConstants::FRCLogger::logType::Info, "Let's Get this Bread");
}

void Robot::TeleopPeriodic() {
  if (m_HID->getButtonPressed(RobotConstants::HID::controllerMappingName::selectButton)) //Switches the drive mode.
  {
    if (m_driveTrain->getCurrentDriveOption() == RobotConstants::DriveTrain::driveOptions::TankDrive)
      m_driveTrain->setDriveOption(RobotConstants::DriveTrain::driveOptions::ArcadeDrive);
    else
      m_driveTrain->setDriveOption(RobotConstants::DriveTrain::driveOptions::TankDrive);
  }

  if (m_driveTrain->getCurrentDriveOption() == RobotConstants::DriveTrain::driveOptions::TankDrive) //Drives tank drive config.
  {
    double leftJoystickDriveValue = m_HID->getAdjustedAxis(RobotConstants::HID::controllerMappingName::leftJoystickYAxis); //Forward/Back (Y Axis).  ^ -- v
    double rightJoystickDriveValue = m_HID->getAdjustedAxis(RobotConstants::HID::controllerMappingName::rightJoystickYAxis); //Forward/Back (Y Axis).  ^ -- v
    m_driveTrain->setDrivePower(leftJoystickDriveValue, rightJoystickDriveValue);
  }
  if (m_driveTrain->getCurrentDriveOption() == RobotConstants::DriveTrain::driveOptions::ArcadeDrive) //Drives arcade drive config.
  {
    double leftJoystickDriveValue = m_HID->getAdjustedAxis(RobotConstants::HID::controllerMappingName::leftJoystickYAxis); //Forward/Back (Y Axis).  ^ -- v
    double rightJoystickRotationValue = m_HID->getAdjustedAxis(RobotConstants::HID::controllerMappingName::rightJoystickXAxis); //Rotation value (X Axis). <-->
    m_driveTrain->setDrivePower(leftJoystickDriveValue, rightJoystickRotationValue);
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
