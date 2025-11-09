/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       sanjaynataraj                                             */
/*    Created:      7/13/2025, 2:55:55 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "hardware.h"
#include <vector>

using namespace vex;
vex::motor test_motor = vex::motor(vex::PORT10, false);
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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // The first half of the motor ports are for the left side, and the second
  // half are for the right side
  // If you need to reverse a motor, make its port number negative
  std::vector<int> ports = {vex::PORT3, vex::PORT4, vex::PORT5, vex::PORT6};
  createDriveMotors(ports);

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
  
  testMotors(2000);

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
  // test_motor.spin(fwd);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    controller userController;
    double controllerFrontBackPosition = -userController.Axis4.position();
    double controllerLeftRightPosition = -userController.Axis3.position();

    drive(controllerFrontBackPosition, controllerLeftRightPosition);

    // Allow the user to control the intake
    if (userController.ButtonY.pressing()) {
      // Reverse the intake
      intakeControl(INTAKE_SPEED_PERCENT);
    } else if (userController.ButtonA.pressing()) {
      // Drive intake forward
      intakeControl(INTAKE_SPEED_PERCENT);
    } else {
      // Stop the intake
      intakeControl(0);
    }

    //Allows the user to raise and lower the arm.
    if (userController.ButtonR1.pressing()) {
      // Raises the arms.
      armControl(ARM_SPEED_PERCENT);
    } else if (userController.ButtonR2.pressing()) {
      // Lowers the arms.
      armControl(ARM_SPEED_PERCENT);
    } else {
      // Stop the arms.
      armControl(0);
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
