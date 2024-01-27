/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       frc1                                                      */
/*    Created:      11/9/2023, 3:53:17 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "hardware.h"
#include "auton_task_tree.h"

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

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  wingletLeft.set(true);
  wingletRight.set(true);
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

  auto root_task = get_auton(TEST_AUTON);
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

void usercontrol(void) {
  // User control code here, inside the loop

  int straightSpeed = 0;
  int turnSpeed = 0;

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    straightSpeed = Controller.Axis3.position();
    turnSpeed = Controller.Axis1.position();

    if ((straightSpeed < 5 || straightSpeed > -5) || (turnSpeed < 5 || turnSpeed > -5)) {
        leftMotors.setVelocity(-(straightSpeed + turnSpeed), percent);
        rightMotors.setVelocity(-(straightSpeed - turnSpeed), percent);
        leftMotors.spin(forward);
        rightMotors.spin(forward);
    } else {
        leftMotors.stop();
        rightMotors.stop();
    }
    
    if (Controller.ButtonUp.pressing()) {
      wingletLeft.set(false);
      wingletRight.set(false);
    } else if (Controller.ButtonDown.pressing()) {
      wingletLeft.set(true);
      wingletRight.set(true);
    }

    // Run the inertial sensor
    if (inertialSensor.installed()) {
        // inertialSensor.startCalibration();
        // Controller.Screen.setCursor(3, 1);
        // Controller.Screen.print("(%2.2f, %2.2f, %2.2f)         ",
        //                         inertialSensor.roll(),
        //                         inertialSensor.pitch(),
        //                         inertialSensor.yaw());
    } else {
      // Controller.Screen.setCursor(3, 1);
      // Controller.Screen.print("Inertial sensor not detected. Check port, wire, or sensor.");
    }

    if(Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing()){
      liftMotor.spin(forward);
    } else if(Controller.ButtonL2.pressing() && !Controller.ButtonL1.pressing()){
      liftMotor.spin(reverse);
    } else {
      liftMotor.stop();
    }

    if(Controller.ButtonR1.pressing()){
      flywheelMotor.spin(forward);
    } else {
      flywheelMotor.stop();
    }

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
