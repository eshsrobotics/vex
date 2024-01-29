/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       frc1                                                      */
/*    Created:      11/9/2023, 3:53:17 PM                                     */
/*    Description:  Entry point for robot; contains auton and teleop code.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "hardware.h"
#include "auton_task_tree.h"

using namespace vex;

// A global instance of competition
competition Competition;

enum FlywheelState {
  // Initial state of the state machine
  // - transitions: default (unconditional)
  START,

  // The state when flywheel is not moving.
  // - transitions:
  //   * R1.pressed() == true: TOGGLE_ON_STATE_PRESSED
  //   * R2.pressed() == true: INSTANTANEOUS_STATE
  //   * else: DEFAULT_STATE
  DEFAULT_STATE,

  // Flywheel activation for triball loads (arm is up)
  // - transitions:
  //   * R1.pressed() == false: TOGGLE_ON_STATE_RELEASED
  //   * R1.pressed() == true: TOGGLE_ON_STATE_PRESSED
  TOGGLE_ON_STATE_PRESSED,

  // Flywheel still activated for triball loads, waiting to turn off (arm is still up)
  // - transitions:
  //   * R1.pressed() == false: TOGGLE_ON_STATE_RELEASED
  //   * R1.pressed() == true: TOGGLE_OFF_STATE_PRESSED
  TOGGLE_ON_STATE_RELEASED,

  // Flywheel deactivated, waiting for user to release (arm is still up)
  // - transitions:
  //   * R1.pressed () == true: TOGGLE_OFF_STATE_PRESSED
  //   * R1.pressed () == false: DEFAULT_STATE
  TOGGLE_OFF_STATE_PRESSED,

  // Flywheel activation for triball intake (arm is down)
  // - transitions:
  //   * R2.pressed() == true: INSTANTANEOUS_STATE
  //   * R2.pressed() == false: DEFAULT_STATE
  INSTANTANEOUS_STATE,

};

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

  FlywheelState flywheelState = START;


  while (true) {
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



    // Our flywheel is at the end of a 4-bar lift.  When it's in the "down"
    // position, it can serve as a triball intake.  In the "up" position, it
    // allows us to  match-load triballs as quickly as possible.

    // The driver asked us to have two "modes" for the flywheel: one where the
    // lift is up, the flywheel is on, and they can just tap a button (R1) to
    // turn the flywheel off; and another where the lift is down in "intake
    // mode" and the driver can tap a button (R2) to turn on the flywheel 'just
    // a little' to suck up a triball.

    // This state machine hopefully implements that request.
    switch (flywheelState) {
      case START:
        flywheelState = DEFAULT_STATE;
        break;

      case DEFAULT_STATE:

        flywheelMotor.stop();
        if (Controller.ButtonR1.pressing()) {
          flywheelState = TOGGLE_ON_STATE_PRESSED;
        } else if (Controller.ButtonR2.pressing()) {
          flywheelState = INSTANTANEOUS_STATE;
        }
        break;

      case TOGGLE_ON_STATE_PRESSED:

        flywheelMotor.spin(forward);
        if (!Controller.ButtonR1.pressing()) {
          flywheelState = TOGGLE_ON_STATE_RELEASED;
        }
        break;

      case TOGGLE_ON_STATE_RELEASED:

        flywheelMotor.spin(forward);
        if (Controller.ButtonR1.pressing()) {
          flywheelState = TOGGLE_OFF_STATE_PRESSED;
        }
        break;

      case TOGGLE_OFF_STATE_PRESSED:

        flywheelMotor.stop();
        if (!Controller.ButtonR1.pressing()) {
          flywheelState = DEFAULT_STATE;
        }
        break;

      case INSTANTANEOUS_STATE:

        flywheelMotor.spin(forward);
        if (!Controller.ButtonR2.pressing()) {
          flywheelState = DEFAULT_STATE;
        }
        break;
    }

    if (Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing()) {
      liftMotor.spin(forward);
    } else if (Controller.ButtonL2.pressing() && !Controller.ButtonL1.pressing()) {
      liftMotor.spin(reverse);
    } else {
      liftMotor.stop();
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
