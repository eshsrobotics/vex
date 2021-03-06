#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RightFront = motor(PORT1, ratio18_1, true);
motor LeftFront = motor(PORT19, ratio18_1, false);
motor RightBack = motor(PORT3, ratio18_1, true);
motor LeftBack = motor(PORT4, ratio18_1, false);
controller Controller1 = controller(primary);
line LeftLineTracker = line(Brain.ThreeWirePort.A);
line MiddleLineTracker = line(Brain.ThreeWirePort.B);
line RightLineTracker = line(Brain.ThreeWirePort.C);
gyro GyroD = gyro(Brain.ThreeWirePort.D);

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