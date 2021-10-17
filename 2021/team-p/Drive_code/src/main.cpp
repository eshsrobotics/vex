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
#include <cmath>

using namespace vex;
using std::abs;
int speed = 50;
int speedSlow = speed / 2;

// Returns the sign of a number: -1 for negative numbers, 1 for positive
// numbers, 0 otherwise
double sgn(double n) {
  if (n > 0) {
    return 1;
  } else if (n < 0) {
    return -1;
  } else {
    return 0;
  }
}

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

bool is_robot_driving() { return Drivetrain.isMoving(); }

bool is_arm_moving() { return (ArmLeft.isSpinning() || ArmRight.isSpinning()); }

// driveFor(forward, x, mm) might not drive that exact number of millimeters


// Moves the arms a certain number of degrees up (+) or down (-)
// PROBLEM: IF THE ARMS ARE BLOCKED BY ANYTHING WHEN IT IS GOING UP, THE
// LOOP WILL CONTINUE FOREVER.
void arms(double dist_degrees, double timeout_msec = 5000) {
  // Takes the gear ratio into account to move the arms by the
  // correct amount of degrees.
  const double GEAR_RATIO = 15;
  dist_degrees *= GEAR_RATIO;

  bool done = false;
  // These variables help the arms move to the desired rotation by
  // accelerating, instead of starting at a certain speed
  // We do not have anything in the function to help with decelerating
  const double MAXIMUM_ARM_LIFT_PERCENT = 25;
  const double ARM_LIFT_ACCELERATION = 0.1;
  double currentVelocityPercent = 0;

  // The arms should be able to stop independently, instead of both arms
  // stopping at the same time,so we need two variables
  bool leftArmSpinning = true;
  bool rightArmSpinning = true;

  // These variables tell us the starting position for the arms, so we
  // know when the motors should stop spinning.
  // Independent of the bump sensors.
  const double STARTING_ROTATION_LEFT = ArmLeft.rotation(deg);
  const double STARTING_ROTATION_RIGHT = ArmRight.rotation(deg);

  // If the motors get stuck, we need the starting time to make an
  // emergency timeout.
  const double STARTING_TIME_MSEC = Brain.timer(msec);

  // The while loop will block the robot until it is done
  // This is not an asynchronous function
  while (!done) {
    // forward means up, unless given a negative value.
    if (leftArmSpinning) {
      ArmLeft.spin(forward, currentVelocityPercent, pct);
    }
    if (rightArmSpinning) {
      ArmRight.spin(forward, currentVelocityPercent, pct);
    }

    // Accelerate in the correct direction.
    if (dist_degrees > 0) {
      currentVelocityPercent += ARM_LIFT_ACCELERATION;
    } else {
      currentVelocityPercent -= ARM_LIFT_ACCELERATION;
    }
    if (abs(currentVelocityPercent) > MAXIMUM_ARM_LIFT_PERCENT) {
      currentVelocityPercent =
          sgn(currentVelocityPercent) * MAXIMUM_ARM_LIFT_PERCENT;
    }

    // Tests if either the RightArmBumper or the LeftArmBumper is being
    // pressed, and if so, stops the arms.
    if (LeftArmBumper.pressing() && dist_degrees < 0) {
      leftArmSpinning = false;
    }
    if (RightArmBumper.pressing() && dist_degrees < 0) {
      rightArmSpinning = false;
    }

    // Stops rotating the arm once rotated the desired degrees.
    if (abs(ArmLeft.rotation(deg) - STARTING_ROTATION_LEFT) >
        abs(dist_degrees)) {
      leftArmSpinning = false;
    }
    if (abs(ArmRight.rotation(deg) - STARTING_ROTATION_RIGHT) >
        abs(dist_degrees)) {
      rightArmSpinning = false;
    }

    // If both arms are not spinning, or if the time running has
    // exceeded the timeout parameter, the while loop will end.
    if ((!leftArmSpinning && !rightArmSpinning) ||
        (Brain.timer(msec) - STARTING_TIME_MSEC > timeout_msec)) {
      done = true;
    }
  }

  // Stops the robot's arms from moving.
  // brakeType brake stops the arms using power, then cuts power.
  // brakeType coast just cuts power.
  // brakeType hold uses power to hold the arms in place.
  // Used brake to save power, but stop the arm.
  ArmLeft.stop(brake);
  ArmRight.stop(brake);
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
  
  // Changes the drive and turn velocity for the robot
  Drivetrain.setDriveVelocity(50, pct);
  Drivetrain.setTurnVelocity(50, pct);
  
  // Puts a ring in the team mobile goal, then moves the mobile goal off
  // of the win point line.
  Drivetrain.turnFor(right, 15, degrees);
  Drivetrain.driveFor(forward, 410, mm);
  arms(-70);
  Drivetrain.driveFor(reverse, 250, mm);
  arms(-100);
  Drivetrain.turnFor(left, 25, degrees);
  Drivetrain.driveFor(forward, 400, mm);
  arms(16.7);
  Drivetrain.driveFor(reverse, 250, mm);
  Drivetrain.turnFor(right, 100, degrees);
  Drivetrain.driveFor(forward, 175, mm);
  arms(-16.7);
  Drivetrain.driveFor(reverse, 400, mm);
  
  // Picks up one of the short mobile goals and takes it back to the team's side.
  Drivetrain.turnFor(left, 150, degrees);
  Drivetrain.driveFor(forward, 900, mm);
  arms(16.7);
  Drivetrain.driveFor(reverse, 850, mm);
  Drivetrain.turnFor(right, 60, degrees);
  arms(-16.7);
  Drivetrain.driveFor(reverse, 250, mm);
  
  // Picks up the tallest mobile goal and moves it to the team's side.
  Drivetrain.turnFor(left, 90, degrees);
  Drivetrain.driveFor(forward, 1500, mm);
  Drivetrain.turnFor(right, 180, degrees);
  Drivetrain.driveFor(forward, 1500, mm);
  arms(-16.7);
  Drivetrain.driveFor(reverse, 250, mm);
  Drivetrain.turnFor(left, 135, degrees);
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
    if (Controller1.ButtonR1.pressing()) {
      ArmLeft.spin(forward, speed, pct);
      ArmRight.spin(forward, speed, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      if (!LeftArmBumper.pressing())
        ArmLeft.spin(reverse, speed, pct);
      if (!RightArmBumper.pressing())
        ArmRight.spin(reverse, speed, pct);
    } else {
      ArmLeft.stop(hold);
      ArmRight.stop(hold);
    }

    // Controls the left shoulder buttons to make the arms go a slower speed
    // (25%)
    if (Controller1.ButtonL1.pressing()) {
      ArmLeft.spin(forward, speedSlow, pct);
      ArmRight.spin(forward, speedSlow, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      if (!LeftArmBumper.pressing())
        ArmLeft.spin(reverse, speedSlow, pct);
      if (!RightArmBumper.pressing())
        ArmRight.spin(reverse, speedSlow, pct);
    } else {
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
