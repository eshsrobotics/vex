// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// BackRight            motor         10              
// FrontLeft            motor         11              
// FrontRight           motor         1               
// BackLeft             motor         12              
// VisionSensor         vision        3               
// Controller1          controller                    
// TapeDetectorFL       line          A               
// TapeDetectorFR       line          B               
// TapeDetectorBL       line          C               
// LineDetectorBR       line          D               
// ---- END VEXCODE CONFIGURED DEVICES ----


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Mary, Caden, Brian, Jackson                               */
/*    Created:      Thu Mar 30 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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

// Overrides tele-op if line is detected.
void dont_cross_the_line(double& forwardBack, double& leftRight, double& rotate) {
  // WARNING: Variable is wrong, just an assumption [we know that the 
  // tape is brighter than floor (so the tape will be represented w/ a higher reflectivity than the floor)]
  const int MAX_FLOOR_REFLECTIVITY = 200;
  bool frontLeftFloor = TapeDetectorFL.reflectivity() < MAX_FLOOR_REFLECTIVITY;
  bool frontRightFloor = TapeDetectorFL.reflectivity() < MAX_FLOOR_REFLECTIVITY;
  bool backLeftFloor = TapeDetectorFL.reflectivity() < MAX_FLOOR_REFLECTIVITY;
  bool backRightFloor = TapeDetectorFL.reflectivity() < MAX_FLOOR_REFLECTIVITY;
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  double forwardBack = 0;
  double leftRight = 0;
  double rotate = 0; 

  while (true) {
    forwardBack = Controller1.Axis3.position(percent);
    leftRight = Controller1.Axis4.position(percent);
    rotate = Controller1.Axis1.position(percent);

    drive(forwardBack, leftRight, rotate);

    wait(50, msec);
  }
}
