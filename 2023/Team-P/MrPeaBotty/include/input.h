#ifndef INPUT_H_IS_INCLUDED
#define INPUT_H_IS_INCLUDED

#include "vex.h"
#include "armSubsystem.h"

// A "control scheme" is a mapping from controller inputs to standard outputs
// that we can use during teleop.
//
// The control scheme consists of two things: A data structure that contains our
// "outputs" and a function that maps inputs to the output structure based on a
// mapping argument.
struct ControlMapping {
    // Joystick channels, regardless of drive scheme.  Values range from -100 to 100.
    double turnLeftRight, driveForwardBack;

    // Arm control.  Values range from -100 to 100.
    double armPower;
    ClawPosition clawPosition;

    // If false, the robot will drive according to a tank drive scheme (the
    // turnLeftRight and driveForwardBack channels will be mathematically
    // translated.)
    bool arcade_drive_enabled;
};

enum DriveScheme {
    // Arcade drive with left joystick (channels 3 and 4.)
    // Right joystick vertical channel (channel 2) controls arm movement.
    // L1 opens the claw; R1 closes it; releasing both buttons makes the claw neutral.
    DEFAULT_DRIVE_SCHEME,

    // Tank drive with both joysticks' vertical channels (channels 2 and 3.)
    // D pad up/down bottoms lift and lower the arm.
    // L1 opens the claw; L2 closes it; the neutral claw state is never reached.
    LEO_DRIVE_SCHEME,
};

ControlMapping getControlMapping(DriveScheme driveScheme);

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