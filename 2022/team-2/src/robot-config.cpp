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
signature VisionSensor__GREEN_BOX = signature (1, 3975, 5549, 4762, -157, 445, 144, 0, 0);
signature VisionSensor__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision VisionSensor = vision (PORT3, 50, VisionSensor__GREEN_BOX, VisionSensor__SIG_2, VisionSensor__SIG_3, VisionSensor__SIG_4, VisionSensor__SIG_5, VisionSensor__SIG_6, VisionSensor__SIG_7);
/*vex-vision-config:end*/
controller Controller1 = controller(primary);
line TapeDetectorFL = line(Brain.ThreeWirePort.A);
line TapeDetectorFR = line(Brain.ThreeWirePort.B);
line TapeDetectorBL = line(Brain.ThreeWirePort.C);
line LineDetectorBR = line(Brain.ThreeWirePort.D);

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