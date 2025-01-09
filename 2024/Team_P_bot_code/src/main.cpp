/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       17475                                                     */
/*    Created:      11/17/2024, 2:33:34 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "hardware.h"

using namespace vex;

// A global instance of competition
competition Competition;

/**
 * Returns the sign of a number -- +1 if it is positive, -1 if it is negative,
 * and 0 otherwise.
 */
double sgn(double n) {
  if (n > 0) {
    return 1;
  } else if (n < 0) {
    return -1;
  } else {
    return 0;
  }
}

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
  
  double forwardBackVelocity = 0;
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    double controllerFrontBackPosition = Controller.Axis3.position(); 
    double controllerLeftRightPosition = Controller.Axis4.position();

    // Make the left and right turn velocity be instant.
    const double turnVelocity = controllerLeftRightPosition;

    if (fabs(controllerFrontBackPosition) > JOYSTICK_DEADZONE) {
      // The user is accelerating.
      //
      // If we are already moving backwards (our velocity is negative), then we
      // need to accelerate backwards, too.
      forwardBackVelocity = forwardBackVelocity + sgn(forwardBackVelocity) * FORWARD_BACK_ACCELERATION;

      if (fabs(forwardBackVelocity) > 1) {
        forwardBackVelocity = sgn(forwardBackVelocity);
      }
    } else {
      // The user has let go of the joystick.  Slow down, regardless of the
      // direction in which we were previously accelerating. 
      forwardBackVelocity = forwardBackVelocity * DECAY_FACTOR;
    }    

    // We are experimenting with an acceleration paradigm for teleop.  The
    // ACCELERATION_ENABLED flag can be set at compile time to determine whether
    // we'll use it or not; drivers were complaining about jerky movements
    // without acceleration, which is why we're trying this in the first place.
    //
    // We'll see how it goes.
    if (ACCELERATION_ENABLED) {
      // We're multiplying forwardBackVelocity by 100 here because due to the
      // nature of the previously used sgn() function, not doing this would mean
      // frontBackVelocity has a maximum range of [-1, 1] while robotDrive's
      // velocity values can be anywhere within a maximum range of [-100, 100]
      robotDrive(forwardBackVelocity * 100, turnVelocity);
    } else {
      robotDrive(controllerFrontBackPosition, controllerLeftRightPosition);       
    }                                                                               

    
    
    
    bool outtake = Controller.ButtonL2.pressing();
    bool intake = Controller.ButtonR2.pressing();
    int intakeOrOuttake = 0;
    if (intake == true) {
      intakeOrOuttake = 1;
    } else if (outtake == true) {
      intakeOrOuttake = -1;
    }

    robotintake(intakeOrOuttake);


    bool uplift = Controller.ButtonUp.pressing();
    bool downlift = Controller.ButtonDown.pressing();
    int lift = 0;
    if (uplift == true) {
      lift = 1;
    } else if (downlift == true) {
      lift = -1;
    }


    robotlift(lift);


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
