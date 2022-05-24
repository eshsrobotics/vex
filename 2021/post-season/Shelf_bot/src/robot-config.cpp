#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor29 armRightInside = motor29(Brain.ThreeWirePort.A, false);
motor29 middleMotor = motor29(Brain.ThreeWirePort.B, true);
motor29 conveyorMotor = motor29(Brain.ThreeWirePort.C, false);
motor29 armLeftInside = motor29(Brain.ThreeWirePort.D, true);
motor29 armLeftOutside = motor29(Brain.ThreeWirePort.E, false);
motor29 leftMotor = motor29(Brain.ThreeWirePort.F, false);
motor29 rightMotor = motor29(Brain.ThreeWirePort.G, true);
motor29 armRightOutside = motor29(Brain.ThreeWirePort.H, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}