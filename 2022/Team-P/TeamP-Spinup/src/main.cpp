// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 3, 2      
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 3, 2      
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 3, 2      
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 3, 2      
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// Controller1          controller
// Intakemotors         motor_group   1, 10
// Drivetrain           drivetrain    4, 5, 3, 2
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor front_left(4);
motor back_left(5);
motor_group left_motor_group(front_left, back_left);

motor front_right(3);
motor back_right(2);
motor_group right_motor_group(front_right, back_right);

// Forward declarations.
void auton_implementation();

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
  auton_implementation();
}

// Time-based autonomous routine for the 2022 Team P 'Bot.  Backs
// off into a roller, rolls it, and then causes general mischief to
// score points.
//
// This autonomous is designed to work with a robot that has started just in
// front of the "hard roller" (the roller that does not have a line of tape
// right next to it) in hopes of conflicting less w/ other alliance partners'
// autonomous routines.
void auton_implementation() {

  // The amount of time to reverse the chassis without also activating the
  // roller.  The goal is for us to make contact with the blue/red roller
  // behind us, then activate the roller motor _while driving backward_ in
  // order to guarantee that it rolls.
  const double REVERSE_DRIVE_MS = 150.0;

  // The roll time ms needs to spin for a certain amount of time
  // in order to attain our team's desired color.
  //
  // The roller should turn counter-clockwise in order to get the color of your
  // team.
  const double ROLL_TIME_MS = 500;

  // This const was set in place in order to tell us what speed the autonous
  // should be at
  const double DRIVE_VELOCITY_PCT = 20;

  const double ROLLER_VELOCITY_PCT = 50;

  const double START_TIME_MS = Brain.timer(msec);

  while (true) {

    double elapsedTimeMs = Brain.timer(msec) - START_TIME_MS;

    if (elapsedTimeMs < REVERSE_DRIVE_MS) {
      // Step 1: Reverse the drive.
      // Drivetrain.drive(reverse, DRIVE_VELOCITY_PCT, velocityUnits::pct);
      left_motor_group.spin(reverse, DRIVE_VELOCITY_PCT, velocityUnits::pct);
    } else if (elapsedTimeMs >= REVERSE_DRIVE_MS &&
               elapsedTimeMs < REVERSE_DRIVE_MS + ROLL_TIME_MS) {
      // Step 2: Activiate the roller.
      Intakemotors.spin(directionType::rev, ROLLER_VELOCITY_PCT, velocityUnits::pct);
    } else {
      // Step 3: Stop the roller.
      Intakemotors.stop();
      // Drivetrain.stop();
      left_motor_group.stop();
    }
  }
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

  Intakemotors.setVelocity(100, percent);

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // This code controls the intake, If you press the up button it will move
    // the discs up and if you press the down button it moves the discs down
    /* if (Controller1.ButtonL1.pressing()) {
      Intakemotors.spin(forward);
    } else if (Controller1.ButtonR1.pressing()) {
      Intakemotors.spin(reverse);
    } else {
      Intakemotors.stop();
    }
 */
    // Make robot be able to move on the ground
    // LeftDriveMotor.setVelocity(Controller1.Axis3.position(), percent);
    // RightDriveMotor.setVelocity(Controller1.Axis2.position(), percent);

    // A deadzone is a term usually applied to robots in which there would be no
    // movement given a threshold closest to zero
    /*const double deadzone = 1;
    if (Controller1.Axis3.position() < deadzone && Controller1.Axis3.position()
    > -deadzone) {
      // deadzone for left axis
      LeftDriveMotor.stop();
    } else {
      LeftDriveMotor.spin(fwd);
    }

    if (Controller1.Axis2.position() < deadzone && Controller1.Axis2.position()
    > -deadzone) {
      // deadzone for right axis
      RightDriveMotor.stop();
    } else {
      RightDriveMotor.spin(fwd);
    }*/

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