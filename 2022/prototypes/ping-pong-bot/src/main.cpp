/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\frc1                                             */
/*    Created:      Thu Mar 09 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// flywheel_Left        motor         8               
// flywheel_Right       motor         9               
// intake               motor         7               
// front_Right_1        motor29       A               
// front_Right_2        motor29       B               
// front_Left_1         motor29       C               
// front_Left_2         motor29       D               
// back_Right_2         motor29       F               
// back_Left_1          motor29       G               
// back_Left_2          motor29       H               
// back_Right_1         motor29       E               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <array>

using namespace vex;

// Make the drive train as simple as possible so there is a foward and backward for 
// the 8 motors insted of working about speed of each motor.
//
// @param leftSpeed Velocity of left side of drive train, ranging from -100 to 100.
void drive (double leftSpeed, double rightSpeed) {
  const double VELOCITY_FACTOR = 1;

  std::array<motor29*, 4> leftMotors = { 
    &back_Left_1, &back_Left_2, &front_Left_1, &front_Left_2
  };
  std::array<motor29*, 4> rightMotors = {
    &back_Right_1, &back_Right_2, &front_Right_1, &front_Right_2
  };
  
  for (motor29* currentMotor : leftMotors) {
    currentMotor->setVelocity(leftSpeed * VELOCITY_FACTOR, pct);
    currentMotor->spin(fwd);
  }

  for (motor29* currentMotor : rightMotors) {
    currentMotor->setVelocity(rightSpeed * VELOCITY_FACTOR, pct);
    currentMotor->spin(fwd);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!  
  vexcodeInit();
  flywheel_Left.setVelocity(100, pct);
  flywheel_Right.setVelocity(100, pct);
  intake.setVelocity(60, pct);
  while (true) {
    flywheel_Left.spin(fwd);
    flywheel_Right.spin(fwd);
    intake.spin(fwd);
    drive(30,30);
    wait(100, msec);  
  }  
}
