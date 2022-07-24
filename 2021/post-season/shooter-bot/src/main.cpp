// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       G               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       F               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       C               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       F               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       B               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       F               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       G               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       F               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       G               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       C               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       D               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       C               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PunchMotor           motor         12              
// IntakeMotor          motor29       D               
// LeftMotor            motor29       H               
// RightMotor           motor29       A               
// TransferMotor        motor29       C               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
bool punchActive = false;
bool transferActive = false;

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

void togglePuncher() { 
  if (punchActive == false) {
    PunchMotor.spin(forward);
    punchActive = true; 
  } else {
    PunchMotor.stop();
    punchActive = false;
  }
  return;
} 

void toggleIntakeMotor() { 
  if (intakeActive == false) {
    IntakeMotor.spin(forward);
    intakeActive = true; 
  } else {
    IntakeMotor.stop();
    intakeActive = false;
  }
  return;
} 

void toggleTransferMotor() { 
  if (transferActive == false) {
    TransferMotor.spin(forward);
    transferActive = true; 
  } else {
    TransferMotor.stop();
    transferActive = false;
  }
  return;
} 

void usercontrol(void) {

  // If the front right shoulder button is pressed, the puncher motor will toggle
  // If the front left shoulder button is pressed, the intake motor will toggle
  // If the back left shoulder button is pressed, the transfer motor will toggle
  Controller1.ButtonR1.pressed(togglePuncher);
  Controller1.ButtonL1.pressed(toggleIntakeMotor);
  Controller1.ButtonL2.pressed(toggleTransferMotor);
  
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

    // While the 'A' button is pressed, the punch motor will spin,
    // when it isn't pressed, it will stop
    if (Controller1.ButtonA.pressing()) {
      PunchMotor.spin(forward);
    } else {
      PunchMotor.stop();
    }

    // While the 'X' button is pressed, the intake motor will spin,
    // when it isn't pressed, it will stop
    if (Controller1.ButtonX.pressing()) {
      IntakeMotor.spin(forward);
    } else {
      IntakeMotor.stop();
    }

    // While the 'B' button is pressed, the conveyor (transfer) motor will spin,
    // when it isn't pressed, it will stop
    if (Controller1.ButtonB.pressing()) {
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
