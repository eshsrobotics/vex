#include "robot-config.h"
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor leftMotorA = motor(front_left_motor_port, gearbox_ratio, false);
motor leftMotorB = motor(center_left_motor_port, gearbox_ratio, false);
motor leftMotorC = motor(back_left_motor_port, gearbox_ratio, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);

motor rightMotorA = motor(front_right_motor_port, gearbox_ratio, true);
motor rightMotorB = motor(center_right_motor_port, gearbox_ratio, true);
motor rightMotorC = motor(back_right_motor_port, gearbox_ratio, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 165, mm, 1);
motor intake_roller_motor = motor(intake_roller_motor_port, true);
// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}