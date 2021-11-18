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

//enum LiftDirection { INWARD, OUTWARD };
// Moves the lfit backward, returns no value, bool either true or false
void MoveLift(LiftDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
 /*  const double LIFT_DRIVE_TIME_MILLISECONDSDOWN = 850; // 20;
  const double LIFT_DRIVE_TIME_MILLISECONDSUP = 750;
  const double LIFT_DRIVE_POWER_PERCENT = 100; */
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

//enum ArmDirection { UP, DOWN };
// Moves the lfit backward, returns no value, bool either true or false
void MoveArm(ArmDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  /* const double ARM_DRIVE_TIME_MILLISECONDSDOWN = 400; // 20;
  const double ARM_DRIVE_TIME_MILLISECONDSUP = 400;
  const double ARM_DRIVE_POWER_PERCENT = 100; */
  directionType armDirection = fwd;

  // motor_group Arm = motor_group(ArmMotorLeft, ArmMotorRight, LiftMotor);

  if (dir == UP) {
    armDirection = forward;

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

//enum forkDirection { up, down };
// Moves the lfit backward, returns no value, bool either true or false
void MovepMotor(forkDirection dir) {

  // when lfitMotor spin direction is forward it means lift moves outward
  const double FORK_DRIVE_TIME_MILLISECONDSDOWN = 200; // 20;
  const double FORK_DRIVE_TIME_MILLISECONDSUP = 150;
  const double FORK_DRIVE_POWER_PERCENT = 100;
  directionType forkDirection = fwd;

  if (dir == up) {
    forkDirection = forward;

    pMotor.spinFor(forkDirection, FORK_DRIVE_TIME_MILLISECONDSUP, msec,
                   FORK_DRIVE_POWER_PERCENT, velocityUnits::pct);

  } else if (dir == down) {
    pMotor.spinFor(forkDirection, FORK_DRIVE_TIME_MILLISECONDSDOWN, msec,
                   FORK_DRIVE_POWER_PERCENT, velocityUnits::pct);

  } else {

    pMotor.stop(hold);
  }
}