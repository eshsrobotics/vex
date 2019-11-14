#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor elevatorMotor = motor(PORT1, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool Controller1UpDownButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // check the Up/Down Buttons status to control elevatorMotor
    if (Controller1.ButtonUp.pressing()) {
      elevatorMotor.spin(forward);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (Controller1.ButtonDown.pressing()) {
      elevatorMotor.spin(reverse);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (!Controller1UpDownButtonsControlMotorsStopped){
      elevatorMotor.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1UpDownButtonsControlMotorsStopped = true;
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