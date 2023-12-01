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

// Catapult mode variable
// Mode 0 is auto, mode 1 is semi-auto, mode 2 is manual
enum CatapultMode {
  AUTO_MODE = 1,
  SEMI_AUTO_MODE = 2,
  MANUAL_MODE = 3,
};
CatapultMode currentMode = AUTO_MODE;

// This is the state machine that runs during the catapult's automatic mode
enum AutoState {
  START,
  STANDBY,
  WAITING_TO_FIRE,
  FIRING_STATE
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

void changeMode() {
  // When the mode goes out of the range, set it back to 0
  switch (currentMode) {
    case AUTO_MODE:
      currentMode = SEMI_AUTO_MODE;
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Catapult: Semi-auto");
      break;
    case SEMI_AUTO_MODE:
      currentMode = MANUAL_MODE;
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Catapult: Manual   ");
      break;
    case MANUAL_MODE:
      currentMode = AUTO_MODE;
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Catapult: Auto     ");
      break;
  }
}

void semiAutoShoot() {
  if (currentMode == SEMI_AUTO_MODE && triballDetector.objectDistance(inches) <= DISTANCE_SENSOR_DETECT_TRIBALL_INCHES) {
    catapult.spinFor(360.0, degrees, false);
  }
}

void usercontrol(void) {
  // User control code here, inside the loop

  Controller.ButtonA.pressed(changeMode);
  Controller.ButtonR1.pressed(semiAutoShoot);

  AutoState state = START;
  const double INITIAL_ROTATION = catapult.position(degrees);
  double currentRotation = catapult.position(degrees);

  double triballDetectionTimeMsec = Brain.timer(msec);
  
  bool leftStop = true;
  bool rightStop = true;

  int leftSpeed = 0;
  int rightSpeed = 0;

  // Print the initial catapult mode
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("Catapult: Auto     ");

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    currentRotation = catapult.position(degrees);

    if (currentMode == AUTO_MODE) {
      // Auto mode
      // will use a state machine

      switch (state) {
        case START:
          state = STANDBY;
          break;

        case STANDBY:
          if (triballDetector.installed()) {
            if (triballDetector.objectDistance(inches) <= DISTANCE_SENSOR_DETECT_TRIBALL_INCHES) {
              triballDetectionTimeMsec = Brain.timer(msec);
              state = WAITING_TO_FIRE;
            }
          } else {
            // Uh-oh, no distance sensor!  Print something.
            // Controller.Screen.setCursor(4, 1);
            // Controller.Screen.print("No distance sensor detected. Check port, cable, or sensor.");

          }
          break;
        
        case WAITING_TO_FIRE:
          // Brain.timer(msec) = current time, triballDetectionTimeMsec = time
          // when the robot detects the triball, MILLISECONDS_TO_SHOOT = waiting
          // period before the catapult starts shooting
          if (Brain.timer(msec) >= triballDetectionTimeMsec + MILLISECONDS_TO_SHOOT)  {
            catapult.spinFor(360.0, degrees, false);
            state = FIRING_STATE;
          }
          break;
        
        case FIRING_STATE:
          if (catapult.isDone()) {
            state = STANDBY;
          }
          break;
      }
    } else if (currentMode == MANUAL_MODE) {
      // Manual mode
      if (Controller.ButtonR1.pressing()) {
        catapult.spin(forward);
      } else {
        catapult.stop();
      }
    }

    // Intake code (3 different modes):
    // - One button (L2) to spin both intake motors inward (load a triball onto
    //   the catapult)
    // - One button (L1) to spin both intake motors outward (Eject a triball)
    // - One button (R2) to spin only the outer motor (to index a triball - to
    //   hold it in our intake so we can drive around with the triball)
    // - If multiple buttons pressed at the same time, don't move the intake
    if (Controller.ButtonL2.pressing() && !Controller.ButtonL1.pressing() && !Controller.ButtonR2.pressing()) {
      intakeIn.spin(forward);
      intakeOut.spin(forward);
    } else if (Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing() && !Controller.ButtonR2.pressing()) {
      intakeIn.spin(reverse);
      intakeOut.spin(reverse);
    } else if (Controller.ButtonR2.pressing() && !Controller.ButtonL2.pressing() && !Controller.ButtonL1.pressing()) {
      intakeIn.stop();
      intakeOut.spin(forward);
    } else {
      intakeIn.stop();
      intakeOut.stop();
    }

    leftSpeed = Controller.Axis3.position();
    rightSpeed = Controller.Axis2.position();

    const int DEADZONE = 5;
    if (fabs(leftSpeed) < DEADZONE) {
      leftSpeed = 0;
    } 
    if (fabs(rightSpeed) < DEADZONE) {
      rightSpeed = 0;
    } 

    if (leftSpeed == 0 && leftStop) {
        leftMotors.stop();
        leftStop = false;
    } else {
        leftStop = true;
    }
    if (rightSpeed == 0 && rightStop) {
        rightMotors.stop();
        rightStop = false;
    } else {
        rightStop = true;
    }

    if (leftStop) {
        leftMotors.setVelocity(leftSpeed, percent);
        leftMotors.spin(forward);
    }
    if (rightStop) {
        rightMotors.setVelocity(rightSpeed, percent);
        rightMotors.spin(forward);
    }

    // Run the inertial sensor
    if (inertialSensor.installed()) {
        // inertialSensor.startCalibration();
        Controller.Screen.setCursor(3, 1);
        Controller.Screen.print("(%2.2f, %2.2f, %2.2f)         ",
                                inertialSensor.roll(),
                                inertialSensor.pitch(),
                                inertialSensor.yaw());
    } else {
      Controller.Screen.setCursor(3, 1);
      Controller.Screen.print("Inertial sensor not detected. Check port, wire, or sensor.");
    }

    Controller.Screen.setCursor(2, 1);
    // Controller.Screen.print("L=%3.2f, R=%3.2f ", leftSpeed, rightSpeed);
    Controller.Screen.print(leftSpeed);
    Controller.Screen.print(" / ");
    Controller.Screen.print(rightSpeed);
    Controller.Screen.print("   ");

    if (currentMode == AUTO_MODE) {
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Catapult: Auto     ");
    } else if (currentMode == SEMI_AUTO_MODE) {
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Catapult: Semi-auto");
    } else if (currentMode == MANUAL_MODE) {
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Catapult: Manual   ");
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
