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
// ArmMotorRight        motor         15
// ArmMotorLeft         motor         12
// PneumaticLeft        digital_out   A
// pMotor               motor         18
// PneumaticRight       digital_out   B
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "Autonomous_Routines.h"
#include "Display_Information.h"
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

// Declare Functions

// Controls the pneumatics

void PneumaticControl();
bool PneumaticState = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  clearAllScreens();
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
  const double LIFT_DRIVE_POWER_PERCENT = 100;
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

enum ArmDirection { UP, DOWN };
// Moves the lfit backward, returns no value, bool either true or false
void MoveArm(ArmDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  const double ARM_DRIVE_TIME_MILLISECONDSDOWN = 400; // 20;
  const double ARM_DRIVE_TIME_MILLISECONDSUP = 400;
  const double ARM_DRIVE_POWER_PERCENT = 100;
  directionType armDirection = fwd;

  motor_group Arm = motor_group(ArmMotorLeft, ArmMotorRight, LiftMotor);

  if (dir == UP) {
    armDirection = forward;

    Arm.spinFor(armDirection, ARM_DRIVE_TIME_MILLISECONDSUP, msec,
                ARM_DRIVE_POWER_PERCENT, velocityUnits::pct);

    Arm.stop(hold);

  } else if (dir == DOWN) {
    Arm.spinFor(armDirection, ARM_DRIVE_TIME_MILLISECONDSDOWN, msec,
                ARM_DRIVE_POWER_PERCENT, velocityUnits::pct);

    Arm.stop(hold);
  } else {

    Arm.stop(hold);
  }
}

enum forkDirection { up, down };
// Moves the lfit backward, returns no value, bool either true or false
void MovepMotor(forkDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  const double FORK_DRIVE_TIME_MILLISECONDSDOWN = 200; // 20;
  const double FORK_DRIVE_TIME_MILLISECONDSUP = 150;
  const double FORK_DRIVE_POWER_PERCENT = 100;
  directionType forkDirection = fwd;

  if (dir == up) {
    forkDirection = forward;

    pMotor.spinFor(forkDirection, FORK_DRIVE_TIME_MILLISECONDSUP, msec,
                   FORK_DRIVE_POWER_PERCENT, velocityUnits::pct);

  } else if (dir == down) {
    pMotor.spinFor(forkDirection, FORK_DRIVE_TIME_MILLISECONDSDOWN, msec,
                   FORK_DRIVE_POWER_PERCENT, velocityUnits::pct);

  } else {

    pMotor.stop(hold);
  }
}

// This is the autonomous code
void autonomous(void) {

  // This will tell us which side of the field we are starting on
  // 1 - Means we are on the left side of the field (The side next to the mobile
  // goal that is on the diagonal line) 2 - Means we are on the right side of
  // the field (The side next to the mobile goal that is on the lever)

  int sideOfField = 1;

  // Right Side Field autonomus code
  if (sideOfField == 1) {
    // Deploy mobile goal lift and arms
    MoveLift(OUTWARD);
    // Drive forward to mobile goal
    Drivetrain.setDriveVelocity(100, percent);
    Drivetrain.driveFor(forward, 15, inches);
    // Move DR4B Up to put donuts in position
    MoveArm(UP);
    // Aim pneumatics arm so it is above mobile goal
    MovepMotor(up);
    MoveLift(INWARD);
    // We need a group for the pneumatics
    PneumaticLeft.set(true);
    PneumaticRight.set(true);
    Drivetrain.driveFor(reverse, 12, inches);
    MoveArm(UP);

    // Drivetrain.setTurnVelocity(100, percent);
    // Drivetrain.turnFor(-70, degrees);
    // Drivetrain.driveFor(forward, 18, inches);
    // MoveLift(OUTWARD);
    // Drivetrain.driveFor(reverse, 10, inches);
    // Drivetrain.turnFor(30, degrees);
    // Drivetrain.driveFor(forward, 55, inches);
    // MoveLift(INWARD);
    // Drivetrain.driveFor(reverse, 50, inches);

    // Left Side Field autonomous code
  } else if (sideOfField == 2) {
    // Deploy mobile goal lift and arms
    MoveLift(OUTWARD);
    // Drive forward to mobile goal
    Drivetrain.setDriveVelocity(100, percent);
    Drivetrain.driveFor(forward, 12, inches);
    // Move DR4B Up to put donuts in position
    MoveArm(UP);
    // Aim pneumatics arm so it is above mobile goal
    MovepMotor(up);
    // Pull in mobile goal for donuts
    MoveLift(INWARD);
    // Release donuts
    // Ensure mobile goal isn't on line by moving backwards
    Drivetrain.driveFor(reverse, 12, inches);
    MoveArm(UP);
    // Drivetrain.setDriveVelocity(100, percentUnits units)
    // Drivetrain.driveFor(forward, double distance, distanceUnits units)
    // Drivetrain.setTurnVelocity(80, percent);
    // Drivetrain.turnFor(forward,  units)MoveLift(OUTWARD);
    // Drivetrain.setDriveVelocity(100, percent);
    // Drivetrain.driveFor(forward, 5, inches);
    // MoveArm(UP);
    // MovepMotor(up);
    // MoveLift(INWARD);
    // Pneumatics1.set(true);
  }

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

// This is for the Right side of the field
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// This is the main execution loop for the user control program.
// Each time through the loop your program should update motor + servo
// values based on feedback from the joysticks.

// ........................................................................
// Insert user code here. This is where you use the joystick values to
// update your motors, etc.
// ........................................................................

void usercontrol(void) {

  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();

  Brain.Screen.setCursor(1, 1);
  Controller1.Screen.setCursor(1, 1);

  // Only attach callback functions onece outside the while loop

  // Activate the pnuematics by looking at the Pneumnatic control function

  Controller1.ButtonB.released(PneumaticControl);

  // User control code here, inside the loop
  while (1) {

    // Moves mobile goal extruder forward or backward

    if (Controller1.ButtonL2.pressing()) {

      LiftMotor.spin(forward, 50, percent);

    } else if (Controller1.ButtonL1.pressing()) {

      LiftMotor.spin(reverse, 50, percent);

    } else {

      LiftMotor.stop(hold);
    }

    // Moves lift up and dwown to pick up donuts

    if (Controller1.ButtonR1.pressing()) {

      ArmMotorLeft.spin(forward, 50, percent);
      ArmMotorRight.spin(forward, 50, percent);

    } else if (Controller1.ButtonR2.pressing()) {

      ArmMotorLeft.spin(reverse, 50, percent);
      ArmMotorRight.spin(reverse, 50, percent);

    } else {

      ArmMotorLeft.stop(hold);
      ArmMotorRight.stop(hold);
    }

    vexcodeInit();

    // Testing the pneumatics on the lift, one on each side
    // Move the pnuematic after the start of the match

    if (Controller1.ButtonA.pressing()) {

      pMotor.spin(forward, 10, percent);

    } else if (Controller1.ButtonY.pressing()) {

      pMotor.spin(reverse, 10, percent);
    } else {
      pMotor.stop(hold);
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

// Functions, place all functions here

// Changes the pneumatic state from ture to false

void PneumaticControl() {

  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();

  if (PneumaticState == true) {

    PneumaticState = false;

    Brain.Screen.printAt(1, 1, "false");
    Controller1.Screen.print("false");

  } else {

    PneumaticState = true;

    Brain.Screen.printAt(1, 1, "true");
    Controller1.Screen.print("true");
  }

  PneumaticLeft.set(PneumaticState);
  PneumaticRight.set(PneumaticState);
}