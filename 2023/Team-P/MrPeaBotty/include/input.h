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
    // Joystick channels for arcade drive.  Values range from -100 to 100.
    double turnLeftRight, driveForwardBack;

    // Joystick channels for tank drive.  Values range from -100 to 100.
    //
    // These two fields are probably not necessary; it is possible to use
    // inverse kinematics to convert the velocities of the left and right
    // wheels into overall forward (== driveForwardBack) and angular (==
    // turnLeftRight) velocities.  See
    // https://acme-robotics.gitbook.io/road-runner/tour/kinematics#forward-kinematics-and-odometry
    // for an analysis.
    //
    // However, doing that properly requires the velocities to have dimensions
    // (in length units per second) and requires knowing the track width
    // (the distance between the left and right wheels, in length units.)
    // Unfortunately, our velocities are unitless percentages, so we'd have to
    // rely on some assumption about the track width (setting it equal to 2,
    // maybe?) in order to make the equations work.
    //
    // Instead of bothering with all that, we just stuffed two extra fields
    // into this struct that are only used by tank drive -- much easier!
    double leftSpeed, rightSpeed;

    // If set to true, this data structure's turnLeftRight and
    // driveForwardBack fields will contain the desired velocities, allowing
    // the robot to drive with an arcade drive scheme.
    //
    // If set to false, this data structure's leftSpeed and rightSpeed fields
    // will contain the desired velocities, allowing the robot to drive with a
    // tank drive scheme.
    bool arcade_drive_enabled;

    // Desired claw position.  Set this to CLAW_NEUTRAL if the human driver
    // doesn't care about the claw position during the current iteration.
    ClawPosition clawPosition;

    // Arm motor control.  Values range from -100 to 100.
    double armPower;
};

enum DriveScheme {
    // Our normal drive scheme, invented by Sanjay and tested in two
    // competitions.
    //
    // - Arcade drive with left joystick (channels 3 and 4.)
    // - Right joystick vertical channel (channel 2) controls arm movement.
    // - Holding L1 opens the claw; holding R1 closes it; releasing both
    //   buttons makes the claw neutral.
    DEFAULT_DRIVE_SCHEME,

    // A new tank drive scheme that keeps important controls on the left side
    // of the controller.
    //
    // - Tank drive with both joysticks' vertical channels (channels 2 and 3.)
    // - D-pad up/down buttons lift and lower the arm.
    // - Pressing L1 opens the claw; pressing L2 closes it; the neutral claw
    //   state is unused, so the claw will always have a powered open or close
    //   in sustain mode.
    LEO_DRIVE_SCHEME,
};

// This function maps controller inputs to a standardized bag of variables.
// That way, the robot doesn't care _how_ the humans drive it; it just cares
// that it gets its marching orders.
//
// @param driveScheme One of the drive scheme constants in the DriveScheme
//                    enumeration above.
// @return Returns a struct that fully describes what values are needed to
//         move the robot.
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
