// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// PunchMotor           motor         5
// IntakeMotor          motor29       D
// LeftMotor            motor29       H
// RightMotor           motor29       A
// TransferMotor        motor29       C
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
// PunchMotor           motor         5
// IntakeMotor          motor29       D
// LeftMotor            motor29       H
// RightMotor           motor29       A
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
bool intakeActive = false;

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

void toggleIntakeMotor() { 
  if (intakeActive == false)
    {
      IntakeMotor.spin(forward);
      intakeActive = true; 
    } else {
      IntakeMotor.stop();
      intakeActive = false;
    }
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

    int rightJoystickValue = Controller1.Axis2.position();
    int leftJoystickValue = Controller1.Axis3.position();

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.print("Right: %d", rightJoystickValue);
    Controller1.Screen.newLine();
    Controller1.Screen.print("Left: %d", leftJoystickValue);

    // If the joysticks are not in the deadband range, the drive code will run
    if (rightJoystickValue > 5) {
      RightMotor.setVelocity(rightJoystickValue, percent);
      RightMotor.spin(forward);
    } else if (rightJoystickValue < -5) {
      RightMotor.setVelocity(-rightJoystickValue, percent);
      RightMotor.spin(reverse);
    } else {
      RightMotor.stop();
    }
    if (leftJoystickValue > 5) {
      LeftMotor.setVelocity(leftJoystickValue, percent);
      LeftMotor.spin(forward);
    } else if (leftJoystickValue < -5) {
      LeftMotor.setVelocity(-leftJoystickValue, percent);
      LeftMotor.spin(reverse);
    } else {
      LeftMotor.stop();
    }

    // If the right shoulder button is pressed, the punch motor will spin,
    // otherwise, it will stop
    if (Controller1.ButtonR1.pressing()) {
      PunchMotor.spin(forward);
    } else {
      PunchMotor.stop();
    }
    // If the top left shoulder button is pressed then released the intake motor will spin,
    // but if the left shoulder button is pressed then released again the intake 
    // motor will stop spining

    
    Controller1.ButtonL1.pressed(toggleIntakeMotor);

    // If the bottom left shoulder button is pressed the transfer motor will spin 
    // and will be stop spining when released 
    if (Controller1.ButtonL2.pressing()) {
      TransferMotor.spin(forward);
    } else {
      TransferMotor.stop();
    }

  }

  wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
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
