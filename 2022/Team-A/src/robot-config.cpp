#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor launcher_left = motor(PORT11, ratio18_1, true);
motor launcher_right = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);
motor intake = motor(PORT19, ratio18_1, true);
motor roller = motor(PORT18, ratio18_1, false);
distance distanceSensor = distance(PORT16);
motor leftDriveMotorA = motor(PORT3, ratio18_1, false);
motor leftDriveMotorB = motor(PORT7, ratio18_1, false);
motor_group leftDrive = motor_group(leftDriveMotorA, leftDriveMotorB);
motor rightDriveMotorA = motor(PORT10, ratio18_1, false);
motor rightDriveMotorB = motor(PORT9, ratio18_1, false);
motor_group rightDrive = motor_group(rightDriveMotorA, rightDriveMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}