#include "vex.h"

// Allows you to control the drive using a tank-drive scheme.
//
// Left and right speed percentages vary from -100.0 to 100.0
void tank_drive(double leftSpeedPercent, double rightSpeedPercent, vex::motor_group& left, vex::motor_group& right);

// Allows you to control the drive using an arcade-drive scheme.
void arcade_drive(double horizontalChannel,
                  double verticalChannel, 
                  vex::motor& frontRight,
                  vex::motor& frontLeft,
                  vex::motor& backRight,
                  vex::motor& backLeft);

// Sets the deadzone, which is a value where anything less will be treated as
// zero input.
const double JOYSTICK_DEADZONE_PERCENT = 1;

// Hold makes it so that the wheel will instantly stop spinning once the
// joystick hits a deadzone.
const vex::brakeType ROBOT_BRAKE_TYPE = vex::brakeType::coast;
