#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor PunchMotor = motor(PORT5, ratio18_1, true);
motor29 IntakeMotor = motor29(Brain.ThreeWirePort.D, false);
motor29 LeftMotor = motor29(Brain.ThreeWirePort.H, true);
motor29 RightMotor = motor29(Brain.ThreeWirePort.A, false);
motor29 TransferMotor = motor29(Brain.ThreeWirePort.C, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}