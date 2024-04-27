// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// VisionSensor         vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// VisionSensor         vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// Vision11             vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// Vision11             vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// Vision11             vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// Vision11             vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intakemotors         motor_group   1, 10           
// Drivetrain           drivetrain    4, 5, 6, 3      
// Flywheel             motor_group   8, 9            
// roller               motor         7               
// expansionLeft        digital_out   A               
// expansionRight       digital_out   B               
// Vision11             vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// Intakemotors         motor_group   1, 10
// Drivetrain           drivetrain    4, 5, 6, 3
// Flywheel             motor_group   8, 9
// roller               motor         7
// expansionLeft        digital_out   A
// expansionRight       digital_out   B
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
#include "vision-sensor-configuration.h"

using namespace vex;

// The code was not working and we figured out that all the ports on our brain
// shifted by one. For example when we tried to spin the motor in port 4 it
// would spin port 5. We added the -1s so it would activate the correct ports.
// We do not know why this is happening.

const int FRONT_LEFT_PORT = 8 - 1;  // we want port 4 to spin
const int FRONT_RIGHT_PORT = 9 - 1; // we want port 3 to spin
const int BACK_RIGHT_PORT = 3 - 1;  // we want port 6 to spin
const int BACK_LEFT_PORT = 2 - 1;   // we want port 5 to spin
const int FLYWHEEL_MAX_SPEED = 80;  // 100 pct power is too much for the field.
const int INTAKE_MAX_SPEED = 100;
const int ROLLER_MAX_SPEED = 100;

motor front_left(FRONT_LEFT_PORT);
motor back_left(BACK_LEFT_PORT);
motor_group left_motor_group(front_left, back_left);

motor front_right(FRONT_RIGHT_PORT);
motor back_right(BACK_RIGHT_PORT);
motor_group right_motor_group(front_right, back_right);

// Forward declarations.
void auton_implementation();

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// This function takes 3 inputs which are the degrees of freedom (foward back
// and left right, and turning) and converts then into 4 outputs (the motor
// speeds).
//
// Arguments:
// - strafeLeftRight: Sideways strafing value from -100 to 100.
//                    Negative numbers strafe left.
// - fowardBack:      Moving foward and backwards value from -100 to 100.
//                    Negative numbers move backwards.
// - turnLeftRight:   Turning counterclockwise and clockwise value from -100 to
// 100.
//                    Negative numbers turn counterclockwise.
void mechDrive(int strafeLeftRight, int forwardBack, int turnLeftRight) {

  double front_right_speed = forwardBack - strafeLeftRight - turnLeftRight;
  double back_right_speed = forwardBack + strafeLeftRight - turnLeftRight;
  double front_left_speed = forwardBack + strafeLeftRight + turnLeftRight;
  double back_left_speed = forwardBack - strafeLeftRight + turnLeftRight;

  // Clamp values between -100 to 100 and spins the motor.
  auto clamp = [](int value, motor &m) {
    if (value < -100) {
      value = -100;
    } else if (value > 100) {
      value = 100;
    } else if (value == 0) {
      m.stop();
      return;
    }
    m.spin(fwd, value, pct);
  };
  clamp(front_right_speed, front_right);
  clamp(front_left_speed, front_left);
  clamp(back_left_speed, back_left);
  clamp(back_right_speed, back_right);
  // front_right.spin(fwd, 50, pct); // This is spinning the front LEFT?!
  // front_left.spin(fwd, 50, pct); // This is spinning the back LEFT?!
  // back_left.spin(fwd, 50, pct); // This is spinning the back RIGHT?!
  // back_right.spin(fwd, 50, pct); // This does NOTHING?!
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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  expansionLeft.set(true);
  expansionRight.set(true);
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
  auton_implementation();
}

// Time-based autonomous routine for the 2022 Team P 'Bot.  Backs
// off into a roller, rolls it, and then causes general mischief to
// score points.
//
// This autonomous is designed to work with a robot that has started just in
// front of the "hard roller" (the roller that does not have a line of tape
// right next to it) in hopes of conflicting less w/ other alliance partners'
// autonomous routines.
void auton_implementation() {

  // The roll time ms needs to spin for a certain amount of time
  // in order to attain our team's desired color.
  //
  // The roller should turn counter-clockwise in order to get the color of your
  // team.
  const double ROLL_TIME_MS = 1080;

  // The amount of time needed to drive sideways in regards to the hard starting
  // position. The roller should move forward and spin in order to turn the
  // roller pin.
  const double DRIVE_SIDEWAYS_MS = 1800;

  const double DRIVE_VELOCITY_PCT = 35;

  const double ROLLER_VELOCITY_PCT = 50;

  const double START_TIME_MS = Brain.timer(msec);

  while (true) {

    double elapsedTimeMs = Brain.timer(msec) - START_TIME_MS;

    if (elapsedTimeMs < DRIVE_SIDEWAYS_MS) {
      // Step 1: Drive robot sideways to its left.
      mechDrive(-DRIVE_VELOCITY_PCT, 0, 0);
    } else if (elapsedTimeMs >= DRIVE_SIDEWAYS_MS &&
               elapsedTimeMs < DRIVE_SIDEWAYS_MS + ROLL_TIME_MS) {
      // Step 2: Activate the roller.
      roller.spin(directionType::rev, ROLLER_VELOCITY_PCT, velocityUnits::pct);

      // Drive forward to maintain contact with the roller pin.
      mechDrive(0, 30, 0);
    } else if (elapsedTimeMs >= DRIVE_SIDEWAYS_MS + ROLL_TIME_MS &&
               elapsedTimeMs <
                   DRIVE_SIDEWAYS_MS + ROLL_TIME_MS + DRIVE_SIDEWAYS_MS) {
      // Step 3: Drive sideways to the right to return to the robot's original
      // position.
      mechDrive(DRIVE_VELOCITY_PCT, 0, 0);
      roller.stop();
    } else {
      // Step 4: Stop the drive.
      mechDrive(0, 0, 0);
    }
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

  Intakemotors.setVelocity(100, percent);

  bool flywheelEnabled = false;
  const double flywheelToggleCooldownSeconds = 0.5;
  double lastFlywheelButtonPressTimeSeconds = 0;

  bool intakeEnabled = false;
  const double intakeToggleCooldownSeconds = 0.5;
  double lastIntakeButtonPressTimeSeconds = 0;

  bool rollerEnabled = false;
  const double rollerToggleCooldwonSeconds = 0.5;
  double lastRollerButtonPressTimeSeconds = 0;

  // User control code here, inside the loop
  while (1) {
    int leftRight = Controller1.Axis4.value();
    int fowardBack = Controller1.Axis3.value();
    int turnValue = Controller1.Axis1.value();
    const double currentTimeSeconds = Brain.timer(sec);
    bool flywheelCooldownExceeded =
        currentTimeSeconds - lastFlywheelButtonPressTimeSeconds >
        flywheelToggleCooldownSeconds;
    bool intakeCooldownExceeded =
        currentTimeSeconds - lastIntakeButtonPressTimeSeconds >
        intakeToggleCooldownSeconds;
      
    mechDrive(leftRight, fowardBack, turnValue);

    if (Controller1.ButtonX.pressing() && flywheelCooldownExceeded) {
      flywheelEnabled = !flywheelEnabled;
      lastFlywheelButtonPressTimeSeconds = currentTimeSeconds;
    }

    if (flywheelEnabled == true) {
      Flywheel.spin(fwd, FLYWHEEL_MAX_SPEED, pct);
    } else {
      Flywheel.stop(brakeType::coast);
    }

    if (Controller1.ButtonL2.pressing() && intakeCooldownExceeded) {
      intakeEnabled = !intakeEnabled;
      lastIntakeButtonPressTimeSeconds = currentTimeSeconds;
    }

    if (intakeEnabled == true) {
      Intakemotors.spin(reverse, INTAKE_MAX_SPEED, pct);
    } else {
      Intakemotors.stop(brakeType::coast);
    }

    rollerEnabled = Controller1.ButtonR2.pressing();

    if (rollerEnabled == true) {
      roller.spin(fwd, ROLLER_MAX_SPEED, pct);
    } else {
      roller.stop();
    }

    if (Controller1.ButtonUp.pressing()) {
      expansionLeft.set(false);
      expansionRight.set(false);
    } else if (Controller1.ButtonDown.pressing()) {
      expansionLeft.set(true);
      expansionRight.set(true);
    }

    int x = 0;
    int center = 150;// The x coordinate for the center of the vision sensor
    int OKError = 50; //Used to set a range of values to count is being just in front.
    if (Controller1.ButtonR1.pressing())
    {
      VisionSensor.takeSnapshot(VisionSensor__BLUE_BASKET);
      if (VisionSensor.largestObject.exists)
      {
        x = VisionSensor.largestObject.centerX;
        if(x< (center-OKError)) //If the object is to the left of center
        {
          right_motor_group.spin(directionType::fwd, 25, velocityUnits::pct);
          left_motor_group.spin(directionType::rev, 25, velocityUnits::pct);
        } else if (x> center + OKError) //If the object is to the right of center
        {
          right_motor_group.spin(directionType::rev, 25, velocityUnits::pct);
          left_motor_group.spin(directionType::fwd, 25, velocityUnits::pct);
        } else //The object is not to the right of center and not to the left of center
        {
          left_motor_group.stop(brakeType::brake);
          right_motor_group.stop(brakeType::brake);
        }
      }
        VisionSensor.takeSnapshot(VisionSensor__RED_BASKET);
      if (VisionSensor.largestObject.exists)
      {
        x = VisionSensor.largestObject.centerX;
        if(x< (center-OKError)) //If the object is to the left of center
        {
          right_motor_group.spin(directionType::fwd, 25, velocityUnits::pct);
          left_motor_group.spin(directionType::rev, 25, velocityUnits::pct);
        } else if (x> center + OKError) //If the object is to the right of center
        {
          right_motor_group.spin(directionType::rev, 25, velocityUnits::pct);
          left_motor_group.spin(directionType::fwd, 25, velocityUnits::pct);
        } else //The object is not to the right of center and not to the left of center
        {
          left_motor_group.stop(brakeType::brake);
          right_motor_group.stop(brakeType::brake);
        }
      }
      task::sleep(100);
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