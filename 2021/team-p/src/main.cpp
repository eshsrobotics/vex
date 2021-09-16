/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Tank Drive                                                */
/*    This sample allows you to control the V5 Clawbot using the both         */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left                 motor         8               
// Right                motor         2               
// Middle               motor         3               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;

  while (true) {
    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorsSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorsSpeed = Controller1.Axis2.position();
    if (Controller1.ButtonR2.pressing()) {
      Middle.spin(forward);
    } else if (Controller1.ButtonL2.pressing()) {
      Middle.spin(reverse);
    } else
      Middle.stop();
    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorsSpeed) < deadband) {
      // Set the speed to zero.
      Left.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      Left.setVelocity(leftMotorsSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorsSpeed) < deadband) {
      // Set the speed to zero
      Right.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      Right.setVelocity(rightMotorsSpeed, percent);
    }

    // Spin both motors in the forward direction.
    Left.spin(forward);
    Right.spin(forward);

    wait(25, msec);
  }
}
