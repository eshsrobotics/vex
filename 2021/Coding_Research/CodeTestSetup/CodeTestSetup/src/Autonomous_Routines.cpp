#include "vex.h"
#include <cmath>

using namespace vex;
using std::abs;
int speed = 50;
int speedSlow = speed / 2;

// Returns the sign of a number: -1 for negative numbers, 1 for positive
// numbers, 0 otherwise
double sgn(double n) {
  if (n > 0) {
    return 1;
  } else if (n < 0) {
    return -1;
  } else {
    return 0;
  }
}

bool is_robot_driving() { return Drivetrain.isMoving(); }

bool is_arm_moving() { return (ArmLeft.isSpinning() || ArmRight.isSpinning()); }

// driveFor(forward, x, inches) does not drive the exact number of inches, the
// average amount to change is to subtract 3.90625
void driveForwardFor(double inch) {
  Drivetrain.driveFor(forward, (inch - 3.90625), inches);
}

void driveReverseFor(double inch) {
  Drivetrain.driveFor(reverse, (inch - 3.90625), inches);
}

// turnFor(right, x, degrees) does not turn for the right number of degrees, to
// turn 90 degrees, you have to enter 70.5 degrees instead, so the change rate
// is around 0.78333
void turnRightFor(double deg) {
  // Uses the drivetrain turn function to turn the robot the number of degrees
  // multiplied by the change rate
  Drivetrain.turnFor(right, (deg * 0.78333), degrees);
}

void turnLeftFor(double deg) {
  Drivetrain.turnFor(left, (deg * 0.78333), degrees);
}

// Moves the arms a certain number of degrees up (+) or down (-)
// PROBLEM: IF THE ARMS ARE BLOCKED BY ANYTHING WHEN IT IS GOING UP, THE
// LOOP WILL CONTINUE FOREVER.
void arms(double dist_degrees) {
  // Takes the gear ratio into account to move the arms by the
  // correct amount of degrees.
  double timeout_msec = 5000;
  const double GEAR_RATIO = 15;
  dist_degrees *= GEAR_RATIO;

  bool done = false;
  // These variables help the arms move to the desired rotation by
  // accelerating, instead of starting at a certain speed
  // We do not have anything in the function to help with decelerating
  const double MAXIMUM_ARM_LIFT_PERCENT = 40;
  const double ARM_LIFT_ACCELERATION = 0.1;
  double currentVelocityPercent = 0;

  // The arms should be able to stop independently, instead of both arms
  // stopping at the same time,so we need two variables
  bool leftArmSpinning = true;
  bool rightArmSpinning = true;

  // These variables tell us the starting position for the arms, so we
  // know when the motors should stop spinning.
  // Independent of the bump sensors.
  const double STARTING_ROTATION_LEFT = ArmLeft.rotation(deg);
  const double STARTING_ROTATION_RIGHT = ArmRight.rotation(deg);

  // If the motors get stuck, we need the starting time to make an
  // emergency timeout.
  const double STARTING_TIME_MSEC = Brain.timer(msec);

  // The while loop will block the robot until it is done
  // This is not an asynchronous function
  while (!done) {
    // forward means up, unless given a negative value.
    if (leftArmSpinning) {
      ArmLeft.spin(forward, currentVelocityPercent, pct);
    }
    if (rightArmSpinning) {
      ArmRight.spin(forward, currentVelocityPercent, pct);
    }

    // Accelerate in the correct direction.
    if (dist_degrees > 0) {
      currentVelocityPercent += ARM_LIFT_ACCELERATION;
    } else {
      currentVelocityPercent -= ARM_LIFT_ACCELERATION;
    }
    if (abs(currentVelocityPercent) > MAXIMUM_ARM_LIFT_PERCENT) {
      currentVelocityPercent =
          sgn(currentVelocityPercent) * MAXIMUM_ARM_LIFT_PERCENT;
    }

    // Tests if either the RightArmBumper or the LeftArmBumper is being
    // pressed, and if so, stops the arms.
    if (LeftArmBumper.pressing() && dist_degrees < 0) {
      leftArmSpinning = false;
    }
    if (RightArmBumper.pressing() && dist_degrees < 0) {
      rightArmSpinning = false;
    }

    // Stops rotating the arm once rotated the desired degrees.
    if (abs(ArmLeft.rotation(deg) - STARTING_ROTATION_LEFT) >
        abs(dist_degrees)) {
      leftArmSpinning = false;
    }
    if (abs(ArmRight.rotation(deg) - STARTING_ROTATION_RIGHT) >
        abs(dist_degrees)) {
      rightArmSpinning = false;
    }

    // If both arms are not spinning, or if the time running has
    // exceeded the timeout parameter, the while loop will end.
    if ((!leftArmSpinning && !rightArmSpinning) ||
        (Brain.timer(msec) - STARTING_TIME_MSEC > timeout_msec)) {
      done = true;
    }
  }

  // Stops the robot's arms from moving.
  // brakeType brake stops the arms using power, then cuts power.
  // brakeType coast just cuts power.
  // brakeType hold uses power to hold the arms in place.
  // Used brake to save power, but stop the arm.
  ArmLeft.stop(brake);
  ArmRight.stop(brake);
}