#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftFront = motor(PORT12, ratio18_1, false);
motor rightFront = motor(PORT13, ratio18_1, false);
motor leftBack = motor(PORT9, ratio18_1, true);
motor rightBack = motor(PORT1, ratio18_1, true);
/*vex-vision-config:begin*/
signature Vision__ORANGE_CUBE = signature (1, 8405, 10185, 9295, -3239, -2757, -2998, 2.5, 0);
signature Vision__GREEN_CUBE = signature (2, -6957, -1143, -4050, -3373, -481, -1927, 0.4, 0);
vision Vision = vision (PORT16, 50, Vision__ORANGE_CUBE, Vision__GREEN_CUBE);
/*vex-vision-config:end*/
line LeftLineTracker = line(Brain.ThreeWirePort.B);
line RightLineTracker = line(Brain.ThreeWirePort.C);
servo Camera_motor = servo(Brain.ThreeWirePort.A);

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