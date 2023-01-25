// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftFlywheel         motor         1               
// rightFlywheel        motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\FRC1                                             */
/*    Created:      Sun Jul 24 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftFlywheel         motor         1               
// rightFlywheel        motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace std;
using namespace vex;

double getflywheelspeed();
double flywheelSpeed = 0;
double flywheelAccel = 0;

double signum(double n) {
  if (n > 0) {
    return 1;
  } else if (n < 0) {
    return -1;
  } else {
    return 0;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
  leftFlywheel.setMaxTorque(100, percent);
  leftFlywheel.setBrake(coast);
  rightFlywheel.setMaxTorque(100, percent);
  rightFlywheel.setBrake(coast);
  
  while(1) {
    leftFlywheel.setVelocity(getflywheelspeed(), percent);
    rightFlywheel.setVelocity(getflywheelspeed(), percent);
    leftFlywheel.spin(vex::forward);
    rightFlywheel.spin(vex::forward);
    Brain.Screen.setCursor(1, 0);
    Brain.Screen.print("Speed: %.2f   ", getflywheelspeed());
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Speed: %.2f   ", getflywheelspeed());
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("L-amps: %.3f   ", leftFlywheel.current(amp));
    Controller1.Screen.setCursor(3, 0);    
    Controller1.Screen.print("R-amps: %.3f    ", rightFlywheel.current(amp));
    Brain.Screen.setCursor(2, 0);
    Brain.Screen.print("L-amps: %.3f ", leftFlywheel.current(amp));
    Brain.Screen.print("- R-amps: %.3f    ", rightFlywheel.current(amp));
  }
 
}

double getflywheelspeed() {
  const double FLYWHEEL_ACCELERATION_INCREMENT = 0.0001;
  double joystickPercent = Controller1.Axis2.position(percent);
  if (joystickPercent != 0) {

    // If the user moves the joystick down while flywheelAccel is positive, flywheelAccel will set to 0 and then decelerate
    // If the user moves the joystick up while flywheelAccel is negative, flywheelAccel will set to 0 and then accelerate
    if (signum(joystickPercent) != signum(flywheelAccel)) {
      flywheelAccel = 0;
    }

    flywheelAccel += joystickPercent * FLYWHEEL_ACCELERATION_INCREMENT;
    flywheelSpeed += flywheelAccel;
  }
  if (flywheelSpeed < 0) {
    flywheelSpeed = 0;
  }
  if (flywheelSpeed > 100) {
    flywheelSpeed = 100;
  }
  return flywheelSpeed;
}
