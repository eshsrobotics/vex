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
// intake               motor         4               
// flywheel             motor         5               
// distanceSensor       distance      11              
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// Returns the sign of X: +1 if positive, -1 if negative, 0 otherwise.
double signum(double x) {
  return (x > 0 ? 1.0 : x < 0 ? -1.0 : 0.0);
}


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

void spinMotors(int left, int right, int deadzone) {
  if (abs(left) <= deadzone) {
    LeftBack.stop();
    LeftMiddle.stop();
    LeftFront.stop();
  } else {
    LeftBack.setVelocity(left, percent);
    LeftMiddle.setVelocity(left, percent);
    LeftFront.setVelocity(left, percent);
    LeftBack.spin(forward);
    LeftMiddle.spin(forward);
    LeftFront.spin(forward);
  }

  if (abs(right) <= deadzone) {
    RightBack.stop();
    RightMiddle.stop();
    RightFront.stop();
  } else {
    RightBack.setVelocity(right, percent);
    RightMiddle.setVelocity(right, percent);
    RightFront.setVelocity(right, percent);
    RightBack.spin(forward);
    RightMiddle.spin(reverse);
    RightFront.spin(reverse);
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  const int DEADZONE = 5;
  double leftVelocity = 0.0, rightVelocity = 0.0;

  // The maximum change in velocity per frame that we allow.  The actual
  // acceleration will tend to be a fraction of this, based on the magnitude of 
  // the joystick channels.
  //
  // A value of 20.0 here capts the maximum velocity at 50% (for reasons that
  // are not clear at all!), but we at least maintain decent control.
  const double ACCELERATION = 20.0;  

  // Left to its own devices, the robot's speed will decay on its own.
  // This happens independently for both sides of the chassis.
  const double VELOCITY_DECAY_FACTOR = 0.60;

  // Don't allow the left or right sides to go faster than this.
  const int MAX_VELOCITY_PERCENT = 100.0;

  // This chassis turns on a dime, and it's actually somewhat hard to control
  // when it's spinning.  So we turn at a slower rate than we drive straight.
  const double TURN_REDUCTION_FACTOR = 0.20;

  // The values for the velocities of the roller/intake and flywheel
  const int INTAKE_VELOCITY_PCT = 50;
  const int FLYWHEEL_VELOCITY_PCT = 100;
  
  // The value for how far the distance sensor will try to detecdt a disc
  const int DISTANCE_SENSOR_DETECTION_MM = 75;

  const brakeType BRAKING_MODE = brakeType::brake;
  LeftBack.setBrake(BRAKING_MODE);
  LeftMiddle.setBrake(BRAKING_MODE);
  LeftFront.setBrake(BRAKING_MODE);
  RightBack.setBrake(BRAKING_MODE);
  RightMiddle.setBrake(BRAKING_MODE);
  RightFront.setBrake(BRAKING_MODE);

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

    leftVelocity += (leftJoystick / 100.0) * ACCELERATION;
    rightVelocity += (rightJoystick / 100.0) * ACCELERATION;
    
    if (fabs(leftVelocity) > MAX_VELOCITY_PERCENT) {
      leftVelocity = MAX_VELOCITY_PERCENT * signum(leftVelocity);
    }

    if (fabs(rightVelocity) > MAX_VELOCITY_PERCENT) {
      rightVelocity = MAX_VELOCITY_PERCENT * signum(rightVelocity);
    }

    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("L - %.2f, R - %.2f     ", leftVelocity, rightVelocity);

    if ((rightJoystick > 0 && leftJoystick > 0) || (rightJoystick < 0 && leftJoystick < 0)) {
      spinMotors(leftJoystick, rightJoystick, DEADZONE);
    } else {
      spinMotors(leftJoystick * TURN_REDUCTION_FACTOR, 
                 rightJoystick * TURN_REDUCTION_FACTOR,
                 DEADZONE);
    }

    // Motion decays on its own if not maintained by the user.
    leftVelocity *= VELOCITY_DECAY_FACTOR;
    rightVelocity *= VELOCITY_DECAY_FACTOR;

    // While L2 is held down, the roller will spin, while it is released, the roller will stop
    if (Controller1.ButtonL1.pressing()) {
      intake.setVelocity(INTAKE_VELOCITY_PCT / 2, percent);
      intake.spin(forward);
    }

    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Distance - %.2f mm     ", distanceSensor.objectDistance(mm));

    // If the distance sensor detects an object within 75 mm (7.5 cm), the shooter will
    // automatically turn on and when R1 is pressed on the controller, the intake will turn on,
    // pushing the disc into the shooter and launching it
    //
    // If the sensor does not detect an object, the intake is automatically on, when R1 is
    // pressed, the shooter turns on, and when L1 is pressed, the intake stops
    if(distanceSensor.objectDistance(mm) < DISTANCE_SENSOR_DETECTION_MM) {
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("Shooter - %.2f     ", flywheel.velocity(pct));
      if(Controller1.ButtonR1.pressing()) {
        intake.setVelocity(INTAKE_VELOCITY_PCT, percent);
        intake.spin(forward);
      } else if (Controller1.ButtonR2.pressing()) {
        intake.setVelocity(INTAKE_VELOCITY_PCT, percent);
        intake.spin(reverse);
        flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT / 4, percent);
        flywheel.spin(reverse);
      } else {
        intake.stop();
        flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT, percent);
        flywheel.spin(forward);
      }
    } else {
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("Shooter - %.2f     ", flywheel.velocity(pct));
      if (Controller1.ButtonR1.pressing()) {
        flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT, percent);
        flywheel.spin(forward);
      } else if (Controller1.ButtonR2.pressing()) {
        intake.setVelocity(INTAKE_VELOCITY_PCT, percent);
        intake.spin(reverse);
        flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT / 4, percent);
        flywheel.spin(reverse);
      } else if (Controller1.ButtonL2.pressing()) {
        intake.stop();
      } else {
        intake.setVelocity(INTAKE_VELOCITY_PCT, percent);
        intake.spin(forward);
        flywheel.stop();
      }
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
