#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor TopIntake = motor(PORT1, ratio18_1, true);
motor LowerIntake = motor(PORT10, ratio18_1, true);
controller Controller1 = controller(primary);
motor LeftDriveMotor = motor(PORT4, ratio18_1, false);
motor RightDriveMotor = motor(PORT3, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}