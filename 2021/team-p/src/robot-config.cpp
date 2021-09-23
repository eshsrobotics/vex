#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Left_Motor = motor(PORT19, ratio18_1, false);
motor Right_Motor = motor(PORT12, ratio18_1, true);
controller Controller1 = controller(primary);
motor Arm_Right = motor(PORT11, ratio18_1, false);
motor Arm_Left = motor(PORT20, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}