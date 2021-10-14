/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
int speed = 50;
int speedSlow = speed/2;

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

// Autonomous and Skills Challenge Support Routines.


bool is_robot_driving() {
    return Drivetrain.isMoving();
}

bool is_arm_moving() {
  return (ArmLeft.isSpinning() || ArmRight.isSpinning());
}

// Drives the robot a certain number of millimeters forward (+) or backward (-).
// Driving operation is asynchronous.
// The motors will continue running after the function ends.
void drive(double distance_mm) {
  if (distance_mm > 0) {
    Drivetrain.driveFor(fwd, distance_mm, mm, false);
  } else if (distance_mm < 0) {
    Drivetrain.driveFor(reverse, distance_mm, mm, false);
  } else {
    Drivetrain.stop();
  }
}

// Moves the arms a certain number of degrees up (+) or down (-)
// NEED TO FIX:
// - The push sensors don't stop the arms as they're moving, they can only keep the arms from starting.
void arms(double dist_degrees) {
  if (dist_degrees > 0) {
    ArmRight.rotateFor(forward, (dist_degrees * 15), degrees, false);
    ArmLeft.rotateFor(forward, (dist_degrees * 15), degrees);
  } else if (dist_degrees < 0) {
    if (!LeftArmBumper.pressing()) {
      ArmLeft.rotateFor(forward, (dist_degrees * 15), degrees, false);
    } else {
      ArmLeft.stop(hold);
    }
    if (!RightArmBumper.pressing()) {
      ArmRight.rotateFor(forward, (dist_degrees * 15), degrees);
    } else {
      ArmRight.stop(hold);
    }
  }
  else {
  ArmLeft.stop(hold);
  ArmRight.stop(hold);
  }
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
  Drivetrain.setDriveVelocity(50, pct);
  Drivetrain.setTurnVelocity(50, pct);
  // arms(-90);
  // Drivetrain.turnFor(right, 15, degrees);
  // Drivetrain.driveFor(forward, 410, mm);
  // arms(-70);
  // Drivetrain.driveFor(reverse, 250, mm);
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
    if(Controller1.ButtonR1.pressing()){
      ArmLeft.spin(forward, speed, pct);
      ArmRight.spin(forward, speed, pct);
    }
    else if(Controller1.ButtonR2.pressing()){
      if(!LeftArmBumper.pressing())
      ArmLeft.spin(reverse, speed, pct);
      if(!RightArmBumper.pressing())
      ArmRight.spin(reverse, speed, pct);
    }
    else {
    ArmLeft.stop(hold);
    ArmRight.stop(hold);
    }

    //Controls the left shoulder buttons to make the arms go a slower speed (25%)
    if(Controller1.ButtonL1.pressing()){
      ArmLeft.spin(forward, speedSlow, pct);
      ArmRight.spin(forward, speedSlow, pct);
    }
    else if(Controller1.ButtonL2.pressing()){
      if(!LeftArmBumper.pressing())
      ArmLeft.spin(reverse, speedSlow, pct);
      if(!RightArmBumper.pressing())
      ArmRight.spin(reverse, speedSlow, pct);
    }
    else {
    ArmLeft.stop(hold);
    ArmRight.stop(hold);
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
