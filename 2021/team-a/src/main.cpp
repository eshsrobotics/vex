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
// Drivetrain           drivetrain    19, 1, 4, 20    
// Controller1          controller                    
// LiftMotor            motor         13              
// ArmMotor1            motor         17              
// ArmMotor2            motor         16              
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

enum LiftDirection { INWARD, OUTWARD };
// Moves the lfit backward, returns no value, bool either true or false
void MoveLift(LiftDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  const double LIFT_DRIVE_TIME_MILLISECONDSDOWN = 850; // 20;
  const double LIFT_DRIVE_TIME_MILLISECONDSUP = 750;
  const double LIFT_DRIVE_POWER_PERCENT = 50;
  directionType spinDirection = fwd;

  if (dir == INWARD) {
    spinDirection = reverse;

    LiftMotor.spinFor(spinDirection, LIFT_DRIVE_TIME_MILLISECONDSDOWN, msec,
                      LIFT_DRIVE_POWER_PERCENT, velocityUnits::pct);

  } else if (dir == OUTWARD) {
    LiftMotor.spinFor(spinDirection, LIFT_DRIVE_TIME_MILLISECONDSUP, msec,
                      LIFT_DRIVE_POWER_PERCENT, velocityUnits::pct);
  }
}

void autonomous(void) {
  Drivetrain.setDriveVelocity(80, percent);
  MoveLift(OUTWARD);
  Drivetrain.driveFor(forward, 12, inches);
  MoveLift(INWARD);
  Drivetrain.setTurnVelocity(100, percent);
  Drivetrain.turnFor(-70, degrees);
  Drivetrain.driveFor(forward, 18, inches);
  MoveLift(OUTWARD);
  Drivetrain.driveFor(reverse, 10, inches);
  Drivetrain.turnFor(30, degrees);
  Drivetrain.driveFor(forward, 55, inches);
  MoveLift(INWARD);
  Drivetrain.driveFor(reverse, 50, inches);

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

    if (Controller1.ButtonL2.pressing())

      LiftMotor.spin(forward, 50, percent);

    else if (Controller1.ButtonR2.pressing())

      LiftMotor.spin(reverse, 50, percent);

    else

      LiftMotor.stop(hold);

    if (Controller1.ButtonL1.pressing()) {

      ArmMotor1.spin(forward, 100, percent);
      ArmMotor2.spin(forward, 100, percent);

    } else if (Controller1.ButtonL2.pressing()) {

      ArmMotor1.spin(reverse, 100, percent);
      ArmMotor2.spin(reverse, 100, percent);
    } else 

      ArmMotor1.stop(hold);
      ArmMotor2.stop(hold);
      
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
