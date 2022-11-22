// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_left           motor         7               
// front_right          motor         10              
// back_left            motor         3               
// back_right           motor         9               
// launcher_left        motor         11              
// launcher_right       motor         13              
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


#include "vex.h"


using namespace vex;

// A global instance of competition
competition Competition;

void winpoint_autonomous();


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
  winpoint_autonomous();
}

void winpoint_autonomous() {
  // Set times for how long the flywheel and intake spin
  const int READY_FLYWHEEL = 5000;
  const int MOVE_INTAKE = 10000;

  
  // Autonomous does not start at zero, when the autonomous routine starts, the match
  // may start minutes later. 
  int start_time_ms = Brain.timer(msec);


  // Set velocities and start spinning the flywheel.
  launcher_left.setVelocity(-100, pct);
  launcher_right.setVelocity(-100, pct);
  launcher_left.spin(forward);
  launcher_right.spin(forward);

  intake.setVelocity(35, percent);

  while(true) {
    int elapsed_time_ms = Brain.timer(msec) - start_time_ms;
    
    // If the flywheel is ready, start the intake
    // After the intake is done moving, stop everything and quit out of the while loop
    if (elapsed_time_ms > READY_FLYWHEEL) {
      intake.spin(forward);
    } else if (elapsed_time_ms > MOVE_INTAKE + READY_FLYWHEEL) {
      intake.stop();
      launcher_left.stop();
      launcher_right.stop();
      break;
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
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
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // Initializes the launcher velocity variable and sets the launcher motors to that amount
    // Initializes the intake velocity variable and sets the intake motor to that amount
    int launcher_velocity = 60;
    int intake_velocity = 35;
    launcher_left.setVelocity(launcher_velocity, pct);
    launcher_right.setVelocity(launcher_velocity, pct);
    intake.setVelocity(intake_velocity, pct);
    
    // Make robot be able to move on the ground
    leftDrive.setVelocity(Controller1.Axis3.position(), percent);
    rightDrive.setVelocity(Controller1.Axis2.position(), percent);

    // A deadzone is a term usually applied to robots in which there would be no movement given a threshold closest to zero
    const double deadzone = 5;
    if (Controller1.Axis3.position() < deadzone && Controller1.Axis3.position() > -deadzone) {
      // deadzone for left axis
      leftDrive.stop();
    } else {
      leftDrive.spin(fwd);
    }

    if (Controller1.Axis2.position() < deadzone && Controller1.Axis2.position() > -deadzone) {
      // deadzone for right axis
      rightDrive.stop();
    } else {
      rightDrive.spin(fwd);
    }

    // While X is held down, the roller will spin, while it is released, the roller will stop
    if (Controller1.ButtonB.pressing()) {
      roller.spin(forward);
    } else {
      roller.stop();
    }

    // If the distance sensor detects an object within 35 mm (3.5 cm), the shooter will
    // automatically turn on and when A is pressed on the controller, the intake will turn on,
    // pushing the disc into the shooter and launching it
    //
    // If the sensor does not detect an object, the intake is automatically on and when A is
    // pressed, the shooter turns on
    if(distanceSensor.objectDistance(mm) < 55) {
      launcher_left.spin(forward);
      launcher_right.spin(forward);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("Left - %.2f     ", launcher_left.velocity(pct));
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("Right - %.2f     ", launcher_right.velocity(pct));
      if(Controller1.ButtonA.pressing()) {
        intake.spin(forward);
      } else if (Controller1.ButtonR1.pressing()) {
        intake.spin(reverse);
      } else {
        intake.stop();
      }
    } else {
      if (Controller1.ButtonA.pressing()) {
        launcher_left.spin(forward);
        launcher_right.spin(forward);
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("Left - %.2f     ", launcher_left.velocity(pct));
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("Right - %.2f     ", launcher_right.velocity(pct));
      } else {
        launcher_left.stop();
        launcher_right.stop();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("Left - %.2f     ", launcher_left.velocity(pct));
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("Right - %.2f     ", launcher_right.velocity(pct));
      }
      if (Controller1.ButtonR1.pressing()) {
        intake.spin(reverse);
      } else {
        intake.spin(forward);
      }
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
