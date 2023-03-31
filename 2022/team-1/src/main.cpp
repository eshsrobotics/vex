/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\eshsp                                            */
/*    Created:      Fri Mar 24 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftFront            motor         12              
// rightFront           motor         13              
// leftBack             motor         9               
// rightBack            motor         1               
// Vision               vision        16              
// LeftLineTracker      line          B               
// RightLineTracker     line          C               
// Camera_motor         servo         A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  int speed;
  int rotate;
  int strafe;
  
while(1==1){
  speed = Controller1.Axis3.position();
  rotate = Controller1.Axis1.position();
  strafe = Controller1.Axis4.position();

  leftFront.setVelocity(speed + rotate + strafe,percent);
  rightFront.setVelocity(speed - rotate - strafe,percent);
  leftBack.setVelocity(speed + rotate - strafe,percent);
  rightBack.setVelocity(speed - rotate + strafe,percent);

  leftFront.spin(forward);
  rightFront.spin(forward);
  leftBack.spin(forward);
  rightBack.spin(forward);
  Brain.Screen.clearLine(1);
  Brain.Screen.print("%d",speed);
}
}

if(Vision.takeSnapshot(Vision__GREEN_CUBE)