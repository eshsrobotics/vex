// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    10, 1, A        
// unused_right_now     motor         6               
// Arm                  motor         20              
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
#include "Autonomous_Routines.h"
#include <memory>
#include <cmath> 

using namespace vex;
using std::abs;
using std::make_shared;
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
  Drivetrain.setDriveVelocity(100, pct);
  Drivetrain.setTurnVelocity(100, pct);
  Drivetrain.setStopping(coast);
  
  auto root_task = get_auton(RAMP_DOWN_WIN_PT);
  execute(root_task);
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
