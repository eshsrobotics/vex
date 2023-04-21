#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftFront = motor(PORT11, ratio18_1, false);
motor rightFront = motor(PORT13, ratio18_1, false);
motor leftBack = motor(PORT9, ratio18_1, true);
motor rightBack = motor(PORT1, ratio18_1, true);
/*vex-vision-config:begin*/
signature VisionSensor__DISLIKED_CUBE = signature (1, 8405, 10185, 9295, -3239, -2757, -2998, 3.5, 0);
signature VisionSensor__LIKED_CUBE = signature (2, -6957, -1143, -4050, -3373, -481, -1927, 0.8, 0);
vision VisionSensor = vision (PORT16, 50, VisionSensor__DISLIKED_CUBE, VisionSensor__LIKED_CUBE);
/*vex-vision-config:end*/
line BackRightTracker = line(Brain.ThreeWirePort.B);
line BackLeftTracker = line(Brain.ThreeWirePort.C);
led LED_RED = led(Brain.ThreeWirePort.D);
motor cameraMotor = motor(PORT10, ratio18_1, true);
line FrontRightTracker = line(Brain.ThreeWirePort.E);
line FrontLeftTracker = line(Brain.ThreeWirePort.F);

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