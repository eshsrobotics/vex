#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor IntakemotorsMotorA = motor(PORT1, ratio18_1, true);
motor IntakemotorsMotorB = motor(PORT10, ratio18_1, false);
motor_group Intakemotors = motor_group(IntakemotorsMotorA, IntakemotorsMotorB);
motor leftMotorA = motor(PORT4, ratio18_1, false);
motor leftMotorB = motor(PORT5, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT6, ratio18_1, true);
motor rightMotorB = motor(PORT3, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 304.79999999999995, 203.2, mm, 1);
motor FlywheelMotorA = motor(PORT8, ratio18_1, false);
motor FlywheelMotorB = motor(PORT9, ratio18_1, true);
motor_group Flywheel = motor_group(FlywheelMotorA, FlywheelMotorB);
motor roller = motor(PORT7, ratio18_1, false);
digital_out expansionLeft = digital_out(Brain.ThreeWirePort.A);
digital_out expansionRight = digital_out(Brain.ThreeWirePort.B);
/*vex-vision-config:begin*/
signature VisionSensor__RED_BASKET = signature (1, 8407, 9149, 8778, -1277, -551, -914, 7.6, 0);
signature VisionSensor__BLUE_BASKET = signature (2, -4587, -2979, -3783, 13927, 20339, 17133, 4.4, 0);
vision VisionSensor = vision (PORT11, 50, VisionSensor__RED_BASKET, VisionSensor__BLUE_BASKET);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control Intakemotors
      if (Controller1.ButtonL1.pressing()) {
        Intakemotors.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        Intakemotors.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        Intakemotors.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}