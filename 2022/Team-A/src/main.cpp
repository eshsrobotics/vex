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
// front_left           motor         7               
// front_right          motor         10              
// back_left            motor         3               
// back_right           motor         9               
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"


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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.


    int launcher_velocity = 100;
    launcher_left.setVelocity(launcher_velocity, pct);
    launcher_right.setVelocity(launcher_velocity, pct);

    double left_axis = Controller1.Axis3.position(pct);
    double right_axis = Controller1.Axis2.position(pct);
    bool launcher_on = false;
    const double launcherButtonTimeoutMilliseconds = 1000.0;
    double time_last_pressed_miliseconds = 0; 


    // If X the button is pressed, toggle the shooter motors on or off
    // and then wait for a certain number of milliseconds for cooldown
    // before allowing the toggle again.

    if (Controller1.ButtonX.pressing()) {      
      const double elapsedMilliseconds = Brain.timer(msec) - time_last_pressed_miliseconds;
      if (elapsedMilliseconds >= launcherButtonTimeoutMilliseconds) {        
        time_last_pressed_miliseconds = Brain.timer(msec);
        launcher_on = !launcher_on;      
      }
    }

    if (launcher_on) {
      launcher_left.spin(forward);
      launcher_right.spin(forward);
    } else {
      launcher_left.stop();
      launcher_right.stop();
    }

    if (launcher_on) {
      launcher_left.spin(forward);
      launcher_right.spin(forward);
    } else {
      launcher_left.stop();
      launcher_right.stop();
    }
    
    //for handling the tank drive:

    const int threshold = 10;

    if (fabs(left_axis) < threshold) {
      left_axis = 0;
      front_left.stop();
      back_left.stop();
    } else {
      front_left.setVelocity(left_axis, pct); 
      back_left.setVelocity(left_axis, pct); 
      front_left.spin(forward);
      back_left.spin(forward);
    }

    if (fabs(right_axis) < threshold) {
      right_axis = 0;
      front_right.stop();
      back_right.stop();
    } else {
      front_right.setVelocity(right_axis, pct); 
      back_right.setVelocity(right_axis, pct); 
      front_right.spin(forward);
      back_right.spin(forward);
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
