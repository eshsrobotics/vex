// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    19, 12          
// unused_right_now     motor         20              
// Arm                  motor         13              
// LeftArmBumper        bumper        G               
// RightArmBumper       bumper        H               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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

  clearAllScreens();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// Autonomous and Skills Challenge Support Routines.

/* bool is_robot_driving() { return Drivetrain.isMoving(); }

bool is_arm_moving() { return (Arm.isSpinning() || ArmRight.isSpinning()); }

// driveFor(forward, x, inches) does not drive the exact number of inches, the
// average amount to change is to subtract 3.90625
void driveForwardFor(double inch) {
  Drivetrain.driveFor(forward, (inch - 3.90625), inches);
}

void driveReverseFor(double inch) {
  Drivetrain.driveFor(reverse, (inch - 3.90625), inches);
}

// turnFor(right, x, degrees) does not turn for the right number of degrees, to
// turn 90 degrees, you have to enter 70.5 degrees instead, so the change rate
// is around 0.78333
void turnRightFor(double deg) {
  // Uses the drivetrain turn function to turn the robot the number of degrees
  // multiplied by the change rate
  Drivetrain.turnFor(right, (deg * 0.78333), degrees);
}

void turnLeftFor(double deg) {
  Drivetrain.turnFor(left, (deg * 0.78333), degrees);
}

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
  const double MAXIMUM_ARM_LIFT_PERCENT = 40;
  const double ARM_LIFT_ACCELERATION = 0.1;
  double currentVelocityPercent = 0;

  // The arms should be able to stop independently, instead of both arms
  // stopping at the same time,so we need two variables
  bool leftArmSpinning = true;
  bool rightArmSpinning = true;

  // These variables tell us the starting position for the arms, so we
  // know when the motors should stop spinning.
  // Independent of the bump sensors.
  const double STARTING_ROTATION_LEFT = Arm.rotation(deg);
  const double STARTING_ROTATION_RIGHT = ArmRight.rotation(deg);

  // If the motors get stuck, we need the starting time to make an
  // emergency timeout.
  const double STARTING_TIME_MSEC = Brain.timer(msec);

  // The while loop will block the robot until it is done
  // This is not an asynchronous function
  while (!done) {
    // forward means up, unless given a negative value.
    if (leftArmSpinning) {
      Arm.spin(forward, currentVelocityPercent, pct);
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
    if (abs(Arm.rotation(deg) - STARTING_ROTATION_LEFT) >
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
  Arm.stop(brake);
  ArmRight.stop(brake);
} */
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
  // Drivetrain.setDriveVelocity(100, pct);
  // Drivetrain.setTurnVelocity(100, pct);

  // arms(-25);
  // turnLeftFor(9);
  // driveForwardFor(19);
  // arms(-30);
  // driveReverseFor(10);
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

bool moveArm(int armSpeed, vex::controller::button &upButton,
             vex::controller::button &downButton) {

  bool buttonPressed = false;

  if (upButton.pressing()) {
    buttonPressed = true;
    Arm.spin(forward, armSpeed, pct);
  } else if (downButton.pressing()) {
    buttonPressed = true;
    if (!LeftArmBumper.pressing()) {
      Arm.spin(reverse, armSpeed, pct);
    } else {
      Arm.stop(hold);
    }
  }
  return buttonPressed;
}

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

    temperatureDisplay();

    // Controls the arms of the robot when the shoulder buttons are pressed

    // The right shoulder buttons move the arms up and down at 50% speed
    // The left shoulder buttons move the arms up and down at 25% speed
    if (!moveArm(speed, Controller1.ButtonR1, Controller1.ButtonR2) &&
        !moveArm(speedSlow, Controller1.ButtonL1, Controller1.ButtonL2)) {
      Arm.stop(hold);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
// Lol xd :9
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
