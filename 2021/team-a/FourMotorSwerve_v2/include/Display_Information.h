#include "vex.h"
#include <initializer_list>
#include <map>
#include <string>
#include <vector>

#ifndef DISPLAY_INFORMATION_H_INCLUDED
#define DISPLAY_INFORMATION_H_INCLUDED

class Motor_Display {
public:
  /// Registers a non-drive-train motor with this object.
  ///
  /// @param motor_name The name you want to use for this motor.  Must be
  ///                   unique.
  /// @param motor      A pointer to the actual vex::motor object.  Warning: the
  ///                   pointer must remain valid for the duration of this
  ///                   object, or undefined behavior will occur.
  void Add_Motor(std::string motor_name, vex::motor *motor);

  /// Registers a drivetrain motor with this object.
  ///
  /// @param motor_name The name you want to use for this motor.  Must be
  ///                   unique, name can overlap with non-drivetrain motor names.
  /// @param motor      A pointer to the actual vex::motor object.  Warning: the
  ///                   pointer must remain valid for the duration of this
  ///                   object, or undefined behavior will occur.
  void Add_Drivetrain_Motor(std::string motor_name, vex::motor *motor);
  /// Display Efficiency info for drivetrain motor on the controller screen.
  void Drivetrain_Efficiency_ControllerDisplay();


private:
  std::map<std::string, vex::motor *> _drivetrain_motors;
  std::map<std::string, vex::motor *> _motors;
};

void clearAllScreens();
void temperatureColour(double temperatureReading);

void Temperature_BrainDisplay();

void Drivetrain_Rotation_ControllerDisplay_Degrees();
void Drivetrain_Rotation_ControllerDisplay_Revolutions();

void Drivetrain_Torque_ControllerDisplay_InchPounds();
void Drivetrain_Torque_ControllerDisplay_NewtonMeters();

void Drivetrain_Current_ControllerDisplay();

void Drivetrain_Power_ControllerDisplay();

void Drivetrain_Voltage_ControllerDisplay_Volts();

void Drivetrain_Temperature_ControllerDisplay_Celsius();
void Drivetrain_Temperature_ControllerDisplay_Fahrenheit();
void Drivetrain_Temperature_ControllerDisplay_Percentage();

void Othermotors_Efficiency_ControllerDisplay();

void Othermotors_Rotation_ControllerDisplay_Degrees();
void Othermotors_Rotation_ControllerDisplay_Revolutions();

void Othermotors_Torque_ControllerDisplay_InchPounds();
void Othermotors_Torque_ControllerDisplay_NewtonMeters();

void Othermotors_Current_ControllerDisplay();

void Othermotors_Power_ControllerDisplay();

void Othermotors_Voltage_ControllerDisplay_Volts();

void Othermotors_Temperature_ControllerDisplay_Celsius();
void Othermotors_Temperature_ControllerDisplay_Fahrenheit();
void Othermotors_Temperature_ControllerDisplay_Percentage();

#endif