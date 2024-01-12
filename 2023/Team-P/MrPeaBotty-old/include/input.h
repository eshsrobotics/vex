#ifndef INPUT_H_IS_INCLUDED
#define INPUT_H_IS_INCLUDED

#include "vex.h"


// Allows you to control the drive using a tank-drive scheme.
//
// Left and right speed percentages vary from -100.0 to 100.0
void tank_drive(double leftSpeedPercent, double rightSpeedPercent, vex::motor_group& left, vex::motor_group& right);

// Allows you to control the drive using an arcade-drive scheme.
void arcade_drive(double horizontalChannel,
                  double verticalChannel,
                  vex::motor_group& left, 
                  vex::motor_group& right);

// Taken from https://xiaoxiae.github.io/Robotics-Simplified-Website/drivetrain-control/arcade-drive/.
void arcade_drive_by_quadrant(double rotate,
                              double drive);

// Sets the deadzone, which is a value where anything less will be treated as
// zero input.
const double JOYSTICK_DEADZONE_PERCENT = 1;

// Hold makes it so that the wheel will instantly stop spinning once the
// joystick hits a deadzone.
const vex::brakeType DRIVE_BRAKE_TYPE = vex::brakeType::coast;




#endif //INPUT_H_IS_INCLUDED