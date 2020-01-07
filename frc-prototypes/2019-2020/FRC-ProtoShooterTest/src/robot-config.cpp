#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor UpperFlywheel = motor(PORT1, ratio18_1, false);
motor LowerFlywheel = motor(PORT2, ratio18_1, false);
pot UpperFlywheelPot = pot(Brain.ThreeWirePort.A);
pot LowerFlywheelPot = pot(Brain.ThreeWirePort.B);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}