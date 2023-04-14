/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Mary, Caden, Brian, Jackson                               */
/*    Created:      Thu Mar 30 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// BackRight            motor         10              
// FrontLeft            motor         11              
// FrontRight           motor         1               
// BackLeft             motor         12              
// VisionSensor         vision        2               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
void drive(double forwardBack, double leftRight, double rotate) {
  //   inputs: x, y, and r

  // flPower = + x + y + r
  // frPower = + x - y - r
  // blPower = + x - y + r
  // brPower = + x + y - r
  FrontLeft.setVelocity(forwardBack + leftRight + rotate, percent);
  FrontLeft.spin(forward);
  FrontRight.setVelocity(forwardBack - leftRight - rotate, percent);
  FrontRight.spin(forward);
  BackLeft.setVelocity(forwardBack - leftRight + rotate, percent);
  BackLeft.spin(forward);
  BackRight.setVelocity(forwardBack + leftRight - rotate, percent);
  BackRight.spin(forward);
} 

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (true) {
    drive(Controller1.Axis3.position(percent), 
          Controller1.Axis4.position(percent),
          Controller1.Axis1.position(percent));

    wait(50, msec);
  }
}
