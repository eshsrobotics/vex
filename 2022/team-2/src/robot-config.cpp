#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor BackRight = motor(PORT10, ratio18_1, false);
motor FrontLeft = motor(PORT11, ratio18_1, true);
motor FrontRight = motor(PORT1, ratio18_1, false);
motor BackLeft = motor(PORT12, ratio18_1, true);
/*vex-vision-config:begin*/
vision VisionSensor = vision (PORT2, 50);
/*vex-vision-config:end*/
controller Controller1 = controller(primary);

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