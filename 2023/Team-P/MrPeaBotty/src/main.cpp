/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       frc1                                                      */
/*    Created:      10/12/2023, 4:08:53 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "input.h"
#include "hardwareConstitution.h"
#include "armSubsystem.h"
#include "auton.h"

using namespace vex;
using std::min;
using std::max;

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

  // Open the arm to trap-jaw position to keep the robot dimensions below 18x18
  // inches
  // moveArm(0, CLAW_OPEN, armMotorLeft, armMotorRight, clawMotor);
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
  calibrateClaw(clawMotor, getBumper());
  executeAutonPlan(autonPlan);
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

  calibrateClaw(clawMotor, getBumper());
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("Uche was here!");
  double velocity_x = 0;
  double velocity_y = 0;
  const double acceleration = 1.0; // Probably too fast
  const double decay = 0.9; // Probably too high.
  const double maximum_velocity = 1000.0; // Probably too high.

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    double horizontalChannel = Controller.Axis4.position();
    double verticalChannel = Controller.Axis3.position();
    // arcade_drive(Controller.Axis4.position(),
    //              Controller.Axis3.position(),
    //              L, R);
    
    // Every frame, if the joystick has a nonzero contribution,
    // we add it to our current velocity vector.  The velocity
    // vector persists from frame to frame, so we'd continue at
    // the same speed forever.  BUT!  See the decay below. 
    velocity_x += horizontalChannel * acceleration;
    velocity_y += verticalChannel * acceleration;
    velocity_x = max(min(maximum_velocity, velocity_x), -maximum_velocity);
    velocity_y = max(min(maximum_velocity, velocity_y), -maximum_velocity);

    arcade_drive_by_quadrant(/* velocity_x */ horizontalChannel, 
                             velocity_y);

    // Causes the robot to slow down naturally without human input.
    velocity_x *= decay;
    velocity_y *= decay;

    ClawState clawState = CLAW_NEUTRAL;
    if (Controller.ButtonL1.pressing() == true)
    {
      clawState = CLAW_OPEN;
    }
    else if (Controller.ButtonR1.pressing() == true)
    {
      clawState = CLAW_CLOSE;
    }

    moveArm (-Controller.Axis2.position(),
             clawState, armMotorLeft, armMotorRight, clawMotor);

    // m.spin(fwd, 100, pct);

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
