/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\FRC1                                             */
/*    Created:      Mon Jan 06 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// UpperFlywheel        motor         1               
// LowerFlywheel        motor         2               
// UpperFlywheelPot     pot           A               
// LowerFlywheelPot     pot           B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

double round(double x, int places) {
  return int(x * pow(10, places)) / pow(10, places);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //SetVelocity
  LowerFlywheel.setVelocity(0, percent); 
  UpperFlywheel.setVelocity(0, percent); 
  
  while(true) {
    double lowerAngle = LowerFlywheelPot.angle(degrees);  
    double upperAngle = UpperFlywheelPot.angle(degrees); 
    
    // Linear interpolation.  The min and max are pure assumptions.
    // 0 <= u <= 1.
    const double POT_RANGE_DEGREES = 265.0;
    const double MAX_ANGLE_DEGREES = 180 + (POT_RANGE_DEGREES / 2); 
    const double MIN_ANGLE_DEGREES = 180 - (POT_RANGE_DEGREES / 2);
    const double uLower = (lowerAngle - MIN_ANGLE_DEGREES) / (MAX_ANGLE_DEGREES - MIN_ANGLE_DEGREES);
    const double uUpper = (upperAngle - MIN_ANGLE_DEGREES) / (MAX_ANGLE_DEGREES - MIN_ANGLE_DEGREES);

    const double MAX_VELOCITY_PERCENT = 100.0;

    // -100 <= v <= 100
    const double vLower = 2 * (uLower - 0.5) * MAX_VELOCITY_PERCENT;
    const double vUpper = 2 * (uUpper - 0.5) * MAX_VELOCITY_PERCENT;

    // Set the velocities based on the values we calculated above.
    //
    // If the velocity is too close to 0, stop the motor.
    const double VELOCITY_THRESHOLD_PERCENT = 5.0;
    if (fabs(vLower) < VELOCITY_THRESHOLD_PERCENT) {
      LowerFlywheel.stop();
    } else {
      if (vLower < 0) {
        LowerFlywheel.spin(reverse);
      } else {
        LowerFlywheel.spin(forward);
      }
      LowerFlywheel.setVelocity(vLower, percent);
    }

    if (fabs(vUpper) < VELOCITY_THRESHOLD_PERCENT) {
      UpperFlywheel.stop();
    } else {
      if (vUpper < 0) {
        UpperFlywheel.spin(reverse);
      } else {
        UpperFlywheel.spin(forward);
      }
      UpperFlywheel.setVelocity(vUpper, percent);
    }

    // Print debugging information.
    Brain.Screen.setCursor(0, 0);
    Brain.Screen.print("Upper: u=");
    Brain.Screen.print(round(uUpper, 2));
    Brain.Screen.print("v=");
    Brain.Screen.print(round(vUpper, 2));
    Brain.Screen.print("  ");

    Brain.Screen.setCursor(1, 0);
    Brain.Screen.print("Lower: u=");
    Brain.Screen.print(round(uLower, 2));
    Brain.Screen.print("v=");
    Brain.Screen.print(round(vLower, 2));
    Brain.Screen.print("  ");
  } // end (loop forever)
}
