// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left_Motor           motor         19              
// Right_Motor          motor         12              
// Controller1          controller                    
// Arm_Right            motor         11              
// Arm_Left             motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left_Motor           motor         19              
// Right_Motor          motor         12              
// Controller1          controller                    
// Arm_Right            motor         11              
// Arm_Left             motor         20              
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
    // Creating liftMotorsSpeed outside of the if statement because if neither
    // button is being pressed, then there will be no variable and the code will
    // error.
    int liftMotorsSpeed = 0;
    if (Controller1.ButtonR1.pressing() == true) {
      liftMotorsSpeed = 20;
    } else if (Controller1.ButtonL1.pressing() == true) {
      liftMotorsSpeed = -20;
    }
    Arm_Right.setVelocity(liftMotorsSpeed, percent);
    Arm_Left.setVelocity(liftMotorsSpeed, percent); 

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorsSpeed) < deadband) {
      // Set the speed to zero.
      Left_Motor.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      Left_Motor.setVelocity(leftMotorsSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorsSpeed) < deadband) {
      // Set the speed to zero
      Right_Motor.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      Right_Motor.setVelocity(rightMotorsSpeed, percent);
    }

    // Spin both motors in the forward direction.
    // This is NOT DEBUGGING, It is used at the end of the loop to drive the
    // motors at the speed that was set
    Left_Motor.spin(forward);
    Right_Motor.spin(forward);
    Arm_Left.spin(forward);
    Arm_Right.spin(forward);
    

    wait(25, msec);
  }
}
