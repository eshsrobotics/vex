/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Wilson Family                                    */
/*    Created:      Mon Sep 14 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightFront           motor         1               
// LeftFront            motor         2               
// RightBack            motor         3               
// LeftBack             motor         4               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// This is a loop fuction for the drive motors
//
// strafeLeftRight: the percentage (-100 to 100) of speed of which the robot will go- either strafing to the left or right
// forwardBack: the percentage (-100 to 100) of speed of which the robot will go- either forward or back 
// turnLeftRight:the percentage (-100 to 100) of speed of which the robot will go-  either turning left or right

void mechDrive(int strafeLeftRight, int forwardBack, int turnLeftRight) {
  
  RightFront.spin(forward, forwardBack - strafeLeftRight - turnLeftRight, percent);
  RightBack.spin(forward, forwardBack + strafeLeftRight - turnLeftRight, percent);
  LeftFront.spin(forward, forwardBack + strafeLeftRight + turnLeftRight, percent);
  LeftBack.spin(forward, forwardBack - strafeLeftRight + turnLeftRight, percent);

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true) {
   int leftright = Controller1.Axis4.position(percent);
   int forwardbackward = Controller1.Axis3.position(percent);
   int turnclockwise = Controller1.Axis1.position(percent);

   mechDrive(leftright, forwardbackward, turnclockwise);

  }
  
}
