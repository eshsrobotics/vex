// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    17, 20, 4, 19   
// Controller1          controller                    
// LeftLiftMotor        motor         3               
// ArmMotorRight        motor         10              
// ArmMotorLeft         motor         16              
// PneumaticSpatula     digital_out   B               
// PneumaticClaw        digital_out   A               
// RightLiftMotor       motor         15              
// ArmGroundLimitSwitch limit         C               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    11, 20, 19, 4   
// Controller1          controller                    
// LeftLiftMotor        motor         3               
// ArmMotorRight        motor         10              
// ArmMotorLeft         motor         16              
// PneumaticSpatula     digital_out   B               
// PneumaticClaw        digital_out   A               
// RightLiftMotor       motor         15              
// ArmGroundLimitSwitch limit         C               
// ---- END VEXCODE CONFIGURED DEVICES ----

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "Autonomous_Routines.h"
#include "Display_Information.h"
#include "vex.h"
#include "task.h"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

//auton type printed on screen
const AutonomousTypes autonType = NO_WINPOINT_MIDD;

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

// Declare Functions

// Controls the pneumatics, chnages staes from true to false or false to true,
// function found at the end of main.cpp

void PneumaticControlClaw();
void PneumaticControlSpatula();

// The state of the claws pneumatic starts false this is changed by the function
// pvoid PneumaticControlClaw();

// Default to a closed state in both teleop and auton 
bool pneumaticClawOpen = false;
// The state of the spatulas pneumatic starts true this is changed by the
// function pvoid PneumaticControlClaw();
// WWARNING must ensure spatula is retracted before it begins
bool spatulaRetracted = true;

// Tracks the encoder position, zero when the robot is start, assuming that the
// lift goes with gravity that the econder value risese in positive directon
// Tested starting from zero where the arm is in rotations when the spatula
// cannot deploy
const double leftLiftMotorLimitDegrees = -300;

void pre_auton(void) {
  // Initializing Robot Configu0ration. DO NOT REMOVE!
  vexcodeInit();
  clearAllScreens();
  Drivetrain.setStopping(coast);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  LeftLiftMotor.setRotation(0, degrees);
  // The folded spatula tongs in the bot's intial positions bump into the front
  // left and front right drive motors. So, at the very beginning of teleop,
  // deploy the spatula out to drop the tongs.
  PneumaticSpatula.set(true);
  spatulaRetracted = true;
  // Pneumatic Claw in closed state intialliy in both tele and auton 
  PneumaticClaw.set(false); 
  pneumaticClawOpen = false;
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.setTurnVelocity(100, percent);
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

enum LiftDirection { INWARD, OUTWARD };
// Moves the lfit backward, returns no value, bool either true or false
void MoveLift(LiftDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  const double LIFT_DRIVE_TIME_MILLISECONDSDOWN = 850; // 20;
  const double LIFT_DRIVE_TIME_MILLISECONDSUP = 750;
  const double LIFT_DRIVE_POWER_PERCENT = 100;
  directionType spinDirection = fwd;

  if (dir == INWARD) {
    
    spinDirection = reverse;

    // LiftMotor.spinFor(spinDirection, LIFT_DRIVE_TIME_MILLISECONDSDOWN, msec,
    // LIFT_DRIVE_POWER_PERCENT, velocityUnits::pct);

  } else if (dir == OUTWARD) {
    // LiftMotor.spinFor(spinDirection, LIFT_DRIVE_TIME_MILLISECONDSUP, msec,
    // LIFT_DRIVE_POWER_PERCENT, velocityUnits::pct);
  }
}

enum ArmDirection { UP, DOWN };
// Moves the lfit backward, returns no value, bool either true or false
void MoveArm(ArmDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  const double ARM_DRIVE_TIME_MILLISECONDSDOWN = 400; // 20;
  const double ARM_DRIVE_TIME_MILLISECONDSUP = 400;
  const double ARM_DRIVE_POWER_PERCENT = 100;
  directionType armDirection = fwd;

  // motor_group Arm = motor_group(ArmMotorLeft, ArmMotorRight, LiftMotor);

  if (dir == UP) {
    armDirection = vex::forward;

    //  Arm.spinFor(armDirection, ARM_DRIVE_TIME_MILLISECONDSUP, msec,
    //              ARM_DRIVE_POWER_PERCENT, velocityUnits::pct);

    //  Arm.stop(hold);

  } else if (dir == DOWN) {
    //  Arm.spinFor(armDirection, ARM_DRIVE_TIME_MILLISECONDSDOWN, msec,
    //             ARM_DRIVE_POWER_PERCENT, velocityUnits::pct);

    //  Arm.stop(hold);
  } else {

    //  Arm.stop(hold);
  }
}

// Returns true if pnuematic arm lift is lowered all the way down.
bool isArmGroundLimitSwitchDepressed() {
  return ArmGroundLimitSwitch.pressing();
}


// This is the autonomous code
void autonomous(void) {                
  auto rootTask = selectAutonomousRoutine(autonType, spatulaRetracted, pneumaticClawOpen);
  execute(rootTask);



  // AUTON FOR DAMIEN COMP 
  // This will tell us which side of the field we are starting on
  // 1 - Means we are on the left side of the field (The side next to the mobile
  // goal that is on the diagonal line) 2 - Means we are on the right side of
  // the field (The side next to the mobile goal that is on the lever)

  //int sideOfField = 1;

  // Right Side Field autonomus code
  //if (sideOfField == 1) {
    // Deploy mobile goal lift and arms
  //  MoveLift(OUTWARD);
    // Drive forward to mobile goal

  //  Drivetrain.driveFor(vex::forward, 15, inches);
    // Move DR4B Up to put donuts in position
  //  MoveArm(UP);
  //  MoveLift(INWARD);
    // We need a group for the pneumatics
  //  Drivetrain.driveFor(reverse, 12, inches);
   // MoveArm(UP);

    // Drivetrain.setTurnVelocity(100, percent);
    // Drivetrain.turnFor(-70, degrees);
    // Drivetrain.driveFor(forward, 18, inches);
    // MoveLift(OUTWARD);
    // Drivetrain.driveFor(reverse, 10, inches);
    // Drivetrain.turnFor(30, degrees);
    // Drivetrain.driveFor(forward, 55, inches);
    // MoveLift(INWARD);
    // Drivetrain.driveFor(reverse, 50, inches);

    // Left Side Field autonomous code
  //} else if (sideOfField == 2) {
    // Deploy mobile goal lift and arms
   // MoveLift(OUTWARD);
    // Drive forward to mobile goal
   // Drivetrain.driveFor(vex::forward, 12, inches);
    // Move DR4B Up to put donuts in position
   // MoveArm(UP);

    // Pull in mobile goal for donuts
  //  MoveLift(INWARD);
    // Release donuts
    // Ensure mobile goal isn't on line by moving backwards
   // Drivetrain.driveFor(reverse, 12, inches);
   // MoveArm(UP);
    // Drivetrain.setDriveVelocity(100, percentUnits units)
    // Drivetrain.driveFor(forward, double distance, distanceUnits units)
    // Drivetrain.setTurnVelocity(80, percent);
    // Drivetrain.turnFor(forward,  units)MoveLift(OUTWARD);
    // Drivetrain.setDriveVelocity(100, percent);
    // Drivetrain.driveFor(forward, 5, inches);
    // MoveArm(UP);
    // MovepMotor(up);
    // MoveLift(INWARD);
    // Pneumatics1.set(true);
  }

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

// This is for the Right side of the field
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// This is the main execution loop for the user control program.
// Each time through the loop your program should update motor + servo
// values based on feedback from the joysticks.

// ........................................................................
// Insert user code here. This is where you use the joystick values to
// update your motors, etc.
// ........................................................................

void usercontrol(void) {

  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();

  // printing the current autonomous selection.
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Auton: %s", autonNames[autonType].c_str());
 
  Brain.Screen.setCursor(1, 1);
  Controller1.Screen.setCursor(1, 1);

  Controller1.Screen.print(Drivetrain.velocity(percent));

  // Only attach callback functions onece outside the while loop

  // Set up callback routines for the pneumatic subsystems.
  //
  // Button A controls the claw.  Button Y controls the spatula.
  // Press Button A changes state of pneumatic spatula to true or false
  // Press Button Y changes state of pneumatic hook to true or false
  // The functions PneumaticControlSpaula and PneumaticControlClaw do the same
  // function, so be careful when specifying in code
  Controller1.ButtonA.released(PneumaticControlSpatula);
  Controller1.ButtonY.released(PneumaticControlClaw);

  // User control code here, inside the loop
  while (1) {

    // Moves mobile goal 90 degree arm forward or backward
    temperatureDisplay();

    if (Controller1.ButtonR1.pressing()) {

      // The Lift moves up (against gravity) 90 degrees
      LeftLiftMotor.spin(vex::forward, 100, percent);
      RightLiftMotor.spin(vex::forward, 100, percent);

      // Mecanically switched the tubing meaning true on the pneumantics now makes the 
      // spatula inside the robot, to ease confusion switchted name to spautulaRetracted
      // So if spatulaRetracted is true the spatula is in the robot 

    } else if (Controller1.ButtonR2.pressing() &&  spatulaRetracted) {

      // When moving the beetle motor down, gravity helps us somewhat.
      const double BEETLE_MOTOR_DOWN_POWER_PERCENT = 40;

      // The lift moves down (toward the ground) 90 degrees, don't do that if
      // the spatula is deployed
      LeftLiftMotor.spin(reverse, BEETLE_MOTOR_DOWN_POWER_PERCENT, percent);
      RightLiftMotor.spin(reverse, BEETLE_MOTOR_DOWN_POWER_PERCENT, percent);

      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("EMC Val=%.2f", LeftLiftMotor.rotation(degrees));

    } else {

      LeftLiftMotor.stop(hold);
      RightLiftMotor.stop(hold);
    }

    // Moves four bar arm up and down to place mobile goals on platforms

    if (Controller1.ButtonL1.pressing()) {

      ArmMotorLeft.spin(vex::forward, 100, percent);
      ArmMotorRight.spin(vex::forward, 100, percent);

    } else if (Controller1.ButtonL2.pressing() && !ArmGroundLimitSwitch.pressing()) {

      ArmMotorLeft.spin(reverse, 80, percent);
      ArmMotorRight.spin(reverse, 80, percent);

    } else {

      ArmMotorLeft.stop(hold);
      ArmMotorRight.stop(hold);
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

// Functions, place all functions here

// Changes the pneumatic state of claw from true to false

void PneumaticControlClaw() {

  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();

  if (pneumaticClawOpen == true) {

    pneumaticClawOpen = false;

    Brain.Screen.printAt(1, 1, "false");
    Controller1.Screen.print("false");

  } else {

    pneumaticClawOpen = true;

    Brain.Screen.printAt(1, 1, "true");
    Controller1.Screen.print("true");
  }

  PneumaticClaw.set(pneumaticClawOpen);
}

// Changes the pneumatic state of spatula from true to false



void PneumaticControlSpatula() {

  if (spatulaRetracted == true) {

    spatulaRetracted = false;

    Brain.Screen.printAt(1, 1, "false");
    Controller1.Screen.print("false");
  

  } else {

    // As you move lift down towards gravity encoder goes to smaller numbers: thats why it is less than or equal to 
     bool isLiftArmDown =
      (LeftLiftMotor.rotation(degrees) <= leftLiftMotorLimitDegrees);

    // P revent the spatula from going out if the lift is down

    if (!isLiftArmDown) {
      spatulaRetracted = true;
      Brain.Screen.printAt(1, 1, "true");
      Controller1.Screen.print("true");
    } else {
      // Because the lift arm is down, do NOT deploy the spatula.
      spatulaRetracted = false;        
    }
  }

  PneumaticSpatula.set(spatulaRetracted);
}