// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// BackRight            motor         10              
// FrontLeft            motor         11              
// FrontRight           motor         1               
// BackLeft             motor         12              
// VisionSensor         vision        3               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// VisionSensor         vision        3               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <vector>

const double MAX_DISTANCE_CUBE_WIDTH_PIXELS = 12;

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

struct VisionTarget {
  double x;
  double y;
  double area; 
  double distanceFeet;
  bool targetFound;
};

VisionTarget locateBestBlock(signature colorSignature, bool hated) {
  VisionSensor.takeSnapshot(colorSignature);
  if (VisionSensor.objectCount == 0) { 
    // No targets found
    return VisionTarget{0, 0, 0, 0, false};
  }

  // One or more targets exist
  std::vector<VisionTarget> goodTargets;

  // Loop over the targets, reject the unfavorable targets
  for (int i = 0; i < VisionSensor.objects.getLength(); i = i + 1) {
    if (VisionSensor.objects[i].height < MAX_DISTANCE_CUBE_WIDTH_PIXELS ||
        VisionSensor.objects[i].width < MAX_DISTANCE_CUBE_WIDTH_PIXELS) {
          // Target is too narrow or too flat 
          continue;
    }

    // Not too small; need to consider this target.
    goodTargets.push_back(VisionTarget{
      double(VisionSensor.objects[i].centerX),
      double(VisionSensor.objects[i].centerY),
      double(VisionSensor.objects[i].height * VisionSensor.objects[i].width),
      0, // TODO: calculate the distance.
      true
    });
  }

  // Return the good target with the largest area
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
