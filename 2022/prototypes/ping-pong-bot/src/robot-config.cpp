#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor flywheel_Left = motor(PORT8, ratio18_1, true);
motor flywheel_Right = motor(PORT9, ratio18_1, false);
motor intake = motor(PORT7, ratio18_1, true);
motor29 front_Right_1 = motor29(Brain.ThreeWirePort.A, false);
motor29 front_Right_2 = motor29(Brain.ThreeWirePort.B, false);
motor29 front_Left_1 = motor29(Brain.ThreeWirePort.C, false);
motor29 front_Left_2 = motor29(Brain.ThreeWirePort.D, false);
motor29 back_Right_2 = motor29(Brain.ThreeWirePort.F, false);
motor29 back_Left_1 = motor29(Brain.ThreeWirePort.G, false);
motor29 back_Left_2 = motor29(Brain.ThreeWirePort.H, false);
motor29 back_Right_1 = motor29(Brain.ThreeWirePort.E, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}