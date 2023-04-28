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
signature VisionSensor__ORANGE_BOX = signature (1, 7903, 9475, 8689, -2675, -2107, -2391, 4.6, 0);
signature VisionSensor__GREEN_BOX = signature (2, -5491, -3289, -4390, -3315, -1509, -2412, 3, 0);
signature VisionSensor__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision VisionSensor = vision (PORT3, 50, VisionSensor__ORANGE_BOX, VisionSensor__GREEN_BOX, VisionSensor__SIG_3, VisionSensor__SIG_4, VisionSensor__SIG_5, VisionSensor__SIG_6, VisionSensor__SIG_7);
/*vex-vision-config:end*/
controller Controller1 = controller(primary);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}