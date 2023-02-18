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
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// distanceSensor       distance      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// ---- END VEXCODE CONFIGURED DEVICES ----
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
enum DriveState {
  STOPPED,
  FORWARD,
  BACKWARD,
  TURNING
};

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

// Returns the absolute value of an input number
int abs(int num) {
  if (num < 0) {
    return -num;
  }
  return num;
}

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
  DriveState current = STOPPED, previous = STOPPED;

  // The amount of frames that user input is ignored to correct the robot's motion
  int correctiveFrames = 0;

  // This is what will happen during the corrective frames instead of using user input
  double correctiveLeftVelocity = 0.0;
  double correctiveRightVelocity = 0.0;
  double correctiveDecay = 0.0;

  int previousLeft = 0;
  int previousRight = 0;

  const int EPSILON = 25;
  const int DEADZONE = 5;

  // The values for the velocities of the roller/intake and flywheel
  const int INTAKE_VELOCITY_PCT = 100;
  const int FLYWHEEL_VELOCITY_PCT = 100;

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

    // Sets the current drive state to whichever state the robot is driving in
    if (leftJoystick < 0 && rightJoystick < 0 && abs(leftJoystick - rightJoystick) < EPSILON) {
      current = BACKWARD;
    } else if (leftJoystick > 0 && rightJoystick > 0 && abs(leftJoystick - rightJoystick) < EPSILON) {
      current = FORWARD;
    } else if (leftJoystick == 0 && rightJoystick == 0) {
      current = STOPPED;
    } else {
      current = TURNING;
    }

    if (current != previous) {
      // The drive state has changed
      // We noticed drifting problems when we drive in a straight line after turning
      if ((previous == TURNING && current == FORWARD) || (previous == TURNING && current == STOPPED)) {
        correctiveFrames = 1;
        correctiveLeftVelocity = -previousLeft * 0.1;
        correctiveRightVelocity = -previousRight * 0.1;
        correctiveDecay = 0.7;
      }
      previous = current;
    }

    Controller1.Screen.clearScreen();

    Controller1.Screen.setCursor(1, 1);
    if (current == STOPPED) {
      Controller1.Screen.print("Current: Stopped");
    } else if (current == TURNING) {
      Controller1.Screen.print("Current: Turning");
    } else if (current == FORWARD) {
      Controller1.Screen.print("Current: Forward");
    } else if (current == BACKWARD) {
      Controller1.Screen.print("Current: Backward");
    }

    Controller1.Screen.setCursor(2, 1);
    if (previous == STOPPED) {
      Controller1.Screen.print("Previous: Stopped");
    } else if (previous == TURNING) {
      Controller1.Screen.print("Previous: Turning");
    } else if (previous == FORWARD) {
      Controller1.Screen.print("Previous: Forward");
    } else if (previous == BACKWARD) {
      Controller1.Screen.print("Previous: Backward");
    }

    if (correctiveFrames > 0) {
      // The robot's driving state changed, use corrective measures
      spinMotors((int)correctiveLeftVelocity, (int)correctiveRightVelocity, 0);
      correctiveLeftVelocity *= correctiveDecay;
      correctiveRightVelocity *= correctiveDecay;
      correctiveFrames--;
    } else {
      // Use user input
      if ((rightJoystick > 0 && leftJoystick > 0) || (rightJoystick < 0 && leftJoystick < 0)) {
        spinMotors(leftJoystick, rightJoystick, DEADZONE);
      } else {
        spinMotors(leftJoystick / 2, rightJoystick / 2, DEADZONE);
      }
    }

    // While L2 is held down, the roller will spin, while it is released, the roller will stop
    if (Controller1.ButtonL1.pressing()) {
      intake.setVelocity(INTAKE_VELOCITY_PCT / 2, percent);
      intake.spin(forward);
    } else {
      intake.stop();
    }

    // If the distance sensor detects an object within 55 mm (5.5 cm), the shooter will
    // automatically turn on and when R1 is pressed on the controller, the intake will turn on,
    // pushing the disc into the shooter and launching it
    //
    // If the sensor does not detect an object, the intake is automatically on, when R1 is
    // pressed, the shooter turns on, and when L1 is pressed, the intake stops
    if(distanceSensor.objectDistance(mm) < 55) {
      flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT, percent);
      flywheel.spin(forward);
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
      }
    } else {
      if (Controller1.ButtonR1.pressing()) {
        flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT, percent);
        flywheel.spin(forward);
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("Shooter - %.2f     ", flywheel.velocity(pct));
      } else {
        flywheel.stop();
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("Shooter - %.2f     ", flywheel.velocity(pct));
      }
      if (Controller1.ButtonR2.pressing()) {
        intake.setVelocity(INTAKE_VELOCITY_PCT, percent);
        intake.spin(reverse);
        flywheel.setVelocity(FLYWHEEL_VELOCITY_PCT / 4, percent);
        flywheel.spin(reverse);
      } else if (Controller1.ButtonL2.pressing()) {
        intake.stop();
      } else {
        intake.setVelocity(INTAKE_VELOCITY_PCT, percent);
        intake.spin(forward);
      }
    }

    previousLeft = leftJoystick;
    previousRight = rightJoystick;

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
