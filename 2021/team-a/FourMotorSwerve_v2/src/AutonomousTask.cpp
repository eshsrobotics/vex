#include "vex.h"

using namespace vex;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// This is the autonomous code
void autonomous(void) {

  // This will tell us which side of the field we are starting on
  // 1 - Means we are on the left side of the field (The side next to the mobile
  // goal that is on the diagonal line) 2 - Means we are on the right side of
  // the field (The side next to the mobile goal that is on the lever)

  int sideOfField = 1;

  // Right Side Field autonomus code
  if (sideOfField == 1) {
    // Deploy mobile goal lift and arms
    MoveLift(OUTWARD);
    // Drive forward to mobile goal
    Drivetrain.setDriveVelocity(100, percent);
    Drivetrain.driveFor(forward, 15, inches);
    // Move DR4B Up to put donuts in position
    MoveArm(UP);
    // Aim pneumatics arm so it is above mobile goal
    MovepMotor(up);
    MoveLift(INWARD);
    // We need a group for the pneumatics
    Drivetrain.driveFor(reverse, 12, inches);
    MoveArm(UP);

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
  } else if (sideOfField == 2) {
    // Deploy mobile goal lift and arms
    MoveLift(OUTWARD);
    // Drive forward to mobile goal
    Drivetrain.setDriveVelocity(100, percent);
    Drivetrain.driveFor(forward, 12, inches);
    // Move DR4B Up to put donuts in position
    MoveArm(UP);
    // Aim pneumatics arm so it is above mobile goal
    MovepMotor(up);
    // Pull in mobile goal for donuts
    MoveLift(INWARD);
    // Release donuts
    // Ensure mobile goal isn't on line by moving backwards
    Drivetrain.driveFor(reverse, 12, inches);
    MoveArm(UP);
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
}