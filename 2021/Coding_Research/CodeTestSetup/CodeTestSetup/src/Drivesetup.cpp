/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

int driveSpeed = 50, driveSpeedSlow = driveSpeed / 2;

bool moveArm(int armSpeed, controller::button &upButton,controller::button &downButton) {

  bool buttonPressed = false;

  if (upButton.pressing()) {
    buttonPressed = true;
    ArmLeft.spin(forward, armSpeed, pct);
    ArmRight.spin(forward, armSpeed, pct);
  } else if (downButton.pressing()) {
    buttonPressed = true;
    if (!LeftArmBumper.pressing()) {
      ArmLeft.spin(reverse, armSpeed, pct);
    } else {
      ArmLeft.stop(hold);
    }
    if (!RightArmBumper.pressing()) {
      ArmRight.spin(reverse, armSpeed, pct);
    } else {
      ArmRight.stop(hold);
    }
  }
  return buttonPressed;
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
clearAllScreens();
temperatureDisplay();
wait(25, msec);

    // Controls the arms of the robot when the shoulder buttons are pressed

    // The right shoulder buttons move the arms up and down at 50% driveSpeed
    // The left shoulder buttons move the arms up and down at 25% driveSpeed
    if (!moveArm(driveSpeed, Controller1.ButtonR1, Controller1.ButtonR2) &&
        !moveArm(driveSpeedSlow, Controller1.ButtonL1, Controller1.ButtonL2)) {
      ArmLeft.stop(hold);
      ArmRight.stop(hold);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}