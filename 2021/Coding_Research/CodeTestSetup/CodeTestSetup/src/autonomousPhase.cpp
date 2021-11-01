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

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // Changes the drive and turn velocity for the robot
  Drivetrain.setDriveVelocity(100, pct);
  Drivetrain.setTurnVelocity(100, pct);

  arms(-25);
  turnLeftFor(9);
  driveForwardFor(19);
  arms(-30);
  driveReverseFor(10);
}