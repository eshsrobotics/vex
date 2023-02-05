/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftBack             motor         8               
// LeftMiddle           motor         9               
// LeftFront            motor         10              
// RightBack            motor         3               
// RightMiddle          motor         2               
// RightFront           motor         1               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    int leftJoystick = Controller1.Axis3.position(percent);
    int rightJoystick = Controller1.Axis2.position(percent);

    if (leftJoystick == 0) {
      LeftBack.stop();
      LeftMiddle.stop();
      LeftFront.stop();
    } else {
      LeftBack.setVelocity(leftJoystick/2, percent);
      LeftMiddle.setVelocity(leftJoystick/2, percent);
      LeftFront.setVelocity(leftJoystick/2, percent);
      LeftBack.spin(forward);
      LeftMiddle.spin(forward);
      LeftFront.spin(forward);
    }

    if (rightJoystick == 0) {
      RightBack.stop();
      RightMiddle.stop();
      RightFront.stop();
    } 
    else {
      RightBack.setVelocity(rightJoystick/2, percent);
      RightMiddle.setVelocity(rightJoystick/2, percent);
      RightFront.setVelocity(rightJoystick/2, percent);
      RightBack.spin(forward);
      RightMiddle.spin(forward);
      RightFront.spin(forward);
    }

    if ((rightJoystick > 0 && leftJoystick > 0) || (rightJoystick < 0 && leftJoystick < 0)) {
      LeftBack.setVelocity(leftJoystick, percent);
      LeftMiddle.setVelocity(leftJoystick, percent);
      LeftFront.setVelocity(leftJoystick, percent);
      LeftBack.spin(forward);
      LeftMiddle.spin(forward);
      LeftFront.spin(forward);
      RightBack.setVelocity(rightJoystick, percent);
      RightMiddle.setVelocity(rightJoystick, percent);
      RightFront.setVelocity(rightJoystick, percent);
      RightBack.spin(forward);
      RightMiddle.spin(forward);
      RightFront.spin(forward);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
