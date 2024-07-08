/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       FRC1                                                      */
/*    Created:      2/23/2024, 6:45:31 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor driveMotor = motor(1-1);
motor turnMotor = motor(2-1);
controller Controller = controller();
brain Brain = brain();

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
  double speed = 0.0;
  double angle = 0.0;
  double gearRatioTurn = 5.0 / 3.0;
  double gearRatioDrive = 5.0 / 1.0;
  double axis3 = 0;
  double axis4 = 0;
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if (Controller.Axis3.value() <= 5 && Controller.Axis3.value() >= -5) {
      axis3 = 0;
    } else {
      axis3 = Controller.Axis3.value();
    }

    if (Controller.Axis4.value() <= 5 && Controller.Axis4.value() >= -5) {
      axis4 = 0;
    } else {
      axis4 = Controller.Axis4.value();
    }

    speed = sqrt(pow(axis3, 2) + pow(axis4, 2));

    // if (axis3 < 0) {
    //   speed = -speed;
    // }

    if (axis4 != 0) {
      angle = atan(axis3/axis4) * 180.0/3.1415926535;
    } else if (axis3 > 0) {
      angle = 90.0;
    } else if (axis3 < 0) {
      angle = -90.0;
    }

    if (turnMotor.position(degrees) >= (angle - 5) * gearRatioTurn && turnMotor.position(degrees) <= (angle + 5) * gearRatioTurn) {
      turnMotor.stop();
    } else if (turnMotor.position(degrees) < (angle - 5) * gearRatioTurn) {
      turnMotor.spin(forward);
    } else if (turnMotor.position(degrees) > (angle + 5) * gearRatioTurn) {
      turnMotor.spin(reverse);
    }

    if (speed == 0) {
      driveMotor.stop();
    } else {
      driveMotor.setVelocity(speed, percent);
      driveMotor.spin(forward);
    }

    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Speed: ");
    Brain.Screen.print(speed);
    Brain.Screen.print("       ");
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Angle: ");
    Brain.Screen.print(angle);
    Brain.Screen.print("       ");

    vex::wait(20, msec); // Sleep the task for a short amount of time to
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
