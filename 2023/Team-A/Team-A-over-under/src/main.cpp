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
  //   * R1.pressed() == true: TOGGLE_ON_STATE_PRESSED_FLYWHEEL_FORWARD
  //   * R2.pressed() == true: TOGGLE_ON_STATE_PRESSED_FLYWHEEL_BACKWARD
  //   * Y.pressed == true: INSTANTANEOUS_STATE
  //   * else: DEFAULT_STATE
  DEFAULT_STATE,

  // Flywheel activation for triball loads, fly_dir = forward (arm is up)
  // - transitions:
  //   * R1.pressed() == false: TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE
  //   * R1.pressed() == true: TOGGLE_ON_STATE_PRESSED_FLYWHEEL_FORWARD
  TOGGLE_ON_STATE_PRESSED_FLYWHEEL_FORWARD,

  // Flywheel activation for triball loads, fly_dir = backward (arm is up)
  // - transitions:
  //   * R2.pressed == true: TOGGLE_ON_STATE_PRESSED_FLYWHEEL_BACKWARD
  //   * R2.pressed == false: TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE
  TOGGLE_ON_STATE_PRESSED_FLYWHEEL_BACKWARD,

  // Flywheel still activated for triball loads, waiting to turn off (arm is still up)
  // - transitions:
  //   * R1.pressed == true and fly_dir == forward: TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE
  //   * R2.pressed == true and fly_dir == backward: TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE
  //   * else: TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE
  TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE,

  // Flywheel has just stopped; waiting for user to release the button.
  // - transitions:
  //   * R1.pressed == true: TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE
  //   * R2.pressed == true: TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE
  //   * R1.pressed == false AND R2.pressed == false: DEFAULT_STATE
  TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE,

  // Flywheel activation for triball intake (arm is down)
  // - transitions:
  //   * Y.pressed() == true: INSTANTANEOUS_STATE
  //   * Y.pressed() == false: DEFAULT_STATE
  INSTANTANEOUS_STATE,
};

enum FlywheelDirection {
  FORWARD,
  BACKWARD
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
  winglet.set(true);
  climbingHook.set(true);
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

  auto root_task = get_auton(ALLIANCE_TRIBALL);
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

  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Arcade code");
  
  int straightSpeed = 0;
  int turnSpeed = 0;

  bool wingletOpen = false;
  bool liftUp = false;

  FlywheelState flywheelState = START;
  FlywheelDirection fly_dir = FORWARD;

  flywheelMotor.setVelocity(100, percent);

  liftMotor.setBrake(hold);


  while (true) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    straightSpeed = -Controller.Axis3.position();
    turnSpeed = Controller.Axis1.position() * 0.75;

    // If the lift is up, the robot will drive and turn at half of the normal
    // speed
    if (liftUp) {
      straightSpeed = straightSpeed / 2;
      turnSpeed = turnSpeed / 2;
    }

    // // If the winglet is open, the robot's front and back are switched so the
    // // winglet side is the front
    // if (wingletOpen) {
    //   straightSpeed = -straightSpeed;
    // }

    if ((straightSpeed < DEADZONE || straightSpeed > -DEADZONE) || (turnSpeed < DEADZONE || turnSpeed > -DEADZONE)) {
        leftMotors.setVelocity(-(straightSpeed + turnSpeed), percent);
        rightMotors.setVelocity(-(straightSpeed - turnSpeed), percent);
        leftMotors.spin(forward);
        rightMotors.spin(forward);
    } else {
        leftMotors.stop();
        rightMotors.stop();
    }

    if (Controller.ButtonUp.pressing()) {
      winglet.set(false);
      wingletOpen = true;
    } else if (Controller.ButtonDown.pressing()) {
      winglet.set(true);
      wingletOpen = false;
    }

    if (Controller.ButtonLeft.pressing()) {
      climbingHook.set(false);
    } else if (Controller.ButtonRight.pressing()) {
      climbingHook.set(true);
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
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.print("START                                         ");
        flywheelMotor.stop();
        break;

      case DEFAULT_STATE:

        if (Controller.ButtonR1.pressing()) {
          flywheelState = TOGGLE_ON_STATE_PRESSED_FLYWHEEL_FORWARD;
          fly_dir = FORWARD;
          flywheelMotor.spin(forward);

          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("TOGGLE_ON_STATE_PRESSED_FLYWHEEL_FORWARD      ");
        } else if (Controller.ButtonR2.pressing()) {
          flywheelState = TOGGLE_ON_STATE_PRESSED_FLYWHEEL_BACKWARD;
          fly_dir = BACKWARD;
          flywheelMotor.spin(reverse);
          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("TOGGLE_ON_STATE_PRESSED_FLYWHEEL_BACKWARD     ");
        } else if (Controller.ButtonY.pressing()) {
          flywheelState = INSTANTANEOUS_STATE;
          flywheelMotor.spin(forward);

          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("INSTANTANEOUS_STATE                           ");
        }
        break;

      case TOGGLE_ON_STATE_PRESSED_FLYWHEEL_FORWARD:

        if (!Controller.ButtonR1.pressing()) {
          flywheelState = TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE;

          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE");
        }
        break;

      case TOGGLE_ON_STATE_PRESSED_FLYWHEEL_BACKWARD:

       if (!Controller.ButtonR2.pressing()) {
        flywheelState = TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE;

        Brain.Screen.setCursor(3, 1);
        Brain.Screen.print("TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE");
       }
       break;

      case TOGGLE_ON_STATE_RELEASED_FLYWHEEL_STILL_ACTIVE:

        if ((Controller.ButtonR1.pressing() && fly_dir == FORWARD) ||
            (Controller.ButtonR2.pressing() && fly_dir == BACKWARD)) {
          flywheelState = TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE;
          flywheelMotor.stop();
          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE   ");
        }
        break;

      case TOGGLE_OFF_STATE_RELEASED_FLYWHEEL_INACTIVE:

        if (!Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing()) {
          flywheelState = DEFAULT_STATE;

          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("DEFAULT_STATE                                 ");
        }
        break;

      case INSTANTANEOUS_STATE:

        if (!Controller.ButtonY.pressing()) {
          flywheelState = DEFAULT_STATE;
          flywheelMotor.stop();
          Brain.Screen.setCursor(3, 1);
          Brain.Screen.print("DEFAULT_STATE                                 ");
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

    if (liftMotor.position(degrees) >= DEGREES_FOR_LIFT_UP) {
      liftUp = true;
    } else {
      liftUp = false;
    }

    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(liftMotor.position(degrees));

    if (Controller.ButtonX.pressing()) {
      Brain.Screen.setCursor(5, 1);
      Brain.Screen.print("Left back: ");
      Brain.Screen.print(leftBackMotor.temperature(fahrenheit));
      Brain.Screen.print("             ");
      Brain.Screen.setCursor(6, 1);
      Brain.Screen.print("Left middle: ");
      Brain.Screen.print(leftTopMotor.temperature(fahrenheit));
      Brain.Screen.print("             ");
      Brain.Screen.setCursor(7, 1);
      Brain.Screen.print("Left front: ");
      Brain.Screen.print(leftFrontMotor.temperature(fahrenheit));
      Brain.Screen.print("             ");
      Brain.Screen.setCursor(8, 1);
      Brain.Screen.print("Right back: ");
      Brain.Screen.print(rightBackMotor.temperature(fahrenheit));
      Brain.Screen.print("             ");
      Brain.Screen.setCursor(9, 1);
      Brain.Screen.print("Right middle: ");
      Brain.Screen.print(rightTopMotor.temperature(fahrenheit));
      Brain.Screen.print("             ");
      Brain.Screen.setCursor(10, 1);
      Brain.Screen.print("Right front: ");
      Brain.Screen.print(rightFrontMotor.temperature(fahrenheit));
      Brain.Screen.print("             ");
      Brain.Screen.setCursor(10, 1);
      Brain.Screen.print("Flywheel: ");
      Brain.Screen.print(flywheelMotor.temperature(fahrenheit));
      Brain.Screen.print("          ");
    }


    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
    vex::wait(100, msec);
  }
}
