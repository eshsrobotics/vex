#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontRightWheel = motor(PORT1, ratio18_1, false);
motor FrontLeftWheel = motor(PORT9, ratio18_1, false);
motor BackRightWheel = motor(PORT3, ratio18_1, false);
motor BackLeftWheel = motor(PORT4, ratio18_1, false);
motor LeftIntake = motor(PORT7, ratio18_1, false);
motor RightIntake = motor(PORT13, ratio18_1, false);
motor IntakeLift = motor(PORT10, ratio6_1, false);
motor TrayPusher = motor(PORT8, ratio18_1, false);
controller Controller1 = controller(primary);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);
led RED_AUTON_LED = led(Brain.ThreeWirePort.B);
led BLUE_AUTON_LED = led(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the X/B buttons status to control TrayPusher
      if (Controller1.ButtonX.pressing()) {
        TrayPusher.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        TrayPusher.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped){
        TrayPusher.stop();
        Controller1XBButtonsControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
}