// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 7, 10, 9     
// intake               motor         20              
// roller               motor         19              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 7, 10, 9     
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 7, 10, 9     
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 7, 10, 9     
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 7, 10, 9     
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 7, 10, 9     
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 6, 10, 9     
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 6, 10, 9     
// intake               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 6, 10, 9     
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    3, 6, 10, 9     
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// back_right           motor         9               
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// back_left            motor         3               
// back_right           motor         9               
// launcher_left        motor         11              
// launcher_right       motor         13              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
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
bool intakeActive = false;
bool shooterActive = false;
directionType intakeDirection = forward;

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

bool disk_is_in = false;
//code for sensor to check if the disk is in the intake
void check_the_disk_presence(bool check)
{
  check = /*readings from sensor*/
}

//stopping the intake as soon as disk is in the intake
if(disk_is_in)
{
  intake.stop();
  launcher_left.spin(forward);
  launcher_right.spin(forward);

  while(/*code to wait for the button Y to be pressed*/)

  intake.spin(forward);
}

void toggleShooter() {
  const int DELAY_MILLISECONDS = 100;
  static int lastMillisecondsPressed = Brain.timer(msec);
  if (Brain.timer(msec) - lastMillisecondsPressed >= DELAY_MILLISECONDS) {
    if (shooterActive) {
      launcher_left.spin(forward);
      launcher_right.spin(forward);
      Controller1.Screen.setCursor(3, 0);
      Controller1.Screen.print("Shooter spinning                   ");
    } else {
      launcher_left.stop();
      launcher_right.stop();
      Controller1.Screen.setCursor(3, 0);
      Controller1.Screen.print("Shooter stopped                   ");
    }
    shooterActive = !shooterActive;
  }
  lastMillisecondsPressed = Brain.timer(msec);
}

void toggleIntake() {
  if (intakeActive) {
    intake.spin(intakeDirection);
    Controller1.Screen.setCursor(2, 0);
    if (intakeDirection == forward) {
      Controller1.Screen.print("Intake forwards                   ");
    } else {
      Controller1.Screen.print("Intake backwards                   ");
    }
  } else {
    intake.stop();
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("Intake stopped                   ");
  }
  intakeActive = !intakeActive;
}

void toggleIntakeDirection() {
  if (intakeDirection == forward) {
    intakeDirection = reverse;
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Intake direction reverse                   ");
  } else {
    intakeDirection = forward;
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Intake direction forward                   ");
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    Controller1.ButtonA.pressed(toggleShooter);
    Controller1.ButtonR1.pressed(toggleIntake);
    Controller1.ButtonLeft.pressed(toggleIntakeDirection);

    int launcher_velocity = 100;
    launcher_left.setVelocity(launcher_velocity, pct);
    launcher_right.setVelocity(launcher_velocity, pct);
    intake.setVelocity(100, pct);
    
    if (Controller1.ButtonB.pressing()) {
      roller.spin(forward);
    } else {
      roller.stop();
    }
    
    

    check_the_disk_presence(disk_is_in);
//stopping the intake as soon as disk is in the intake
if(disk_is_in)
{
  intake.stop();
  launcher_left.spin(forward);
  launcher_right.spin(forward);

  while(/*code to wait for the button Y to be pressed*/)
  {
    /*check if the button is is still not pressed*/
  }

  intake.spin(forward);
  wait(3,sec);
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
