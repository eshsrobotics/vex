// PROTOTYPES.CPP -- Implementation file for PROTOTYPE.H
#include <algorithm>    // min, max
#include <sstream>      // stringstream
#include <iomanip>      // setprecision
#include "prototypes.h"
#include "robot-config.h"

using std::min;
using std::max;
using std::stringstream;
using std::setprecision;
using namespace vex;

// This is the maximum controller joystick input threshold that has to be
// overcome for inputs to be registered.
const double DEADZONE = 0.1;

/**
 * Internal helper function for differential driving with arcade-style controls.
 */
void arcade_drive(double straightSpeed, double turnSpeed, motor_group& left,
                  motor_group& right) {

    // We do not want any minor mis-inputs to throw the robot off-course.
    if (abs(straightSpeed) < DEADZONE) {
        straightSpeed = 0;
    }
    if (abs(turnSpeed) < DEADZONE) {
        turnSpeed = 0;
    }

    //This is an arcade drive formula translation. We want to ensure that the
    // actual speed that were are passing into setVelocity is a value between 1
    // and -1.

    // Clamp the input to the interval [-1, 1].
    double sum = straightSpeed + turnSpeed;
    double difference = straightSpeed - turnSpeed;
    sum = max(-1.0, min(sum, 1.0));
    difference = max(-1.0, min(difference, 1.0));
    const double leftVelocity = -(sum);
    const double rightVelocity =-(difference);

    if (rightVelocity != 0) {
        right.setVelocity(rightVelocity * 100, percent);
        right.spin(forward);
    } else {
        right.stop();
    }

    if (leftVelocity != 0) {
        left.setVelocity(leftVelocity * 100, percent);
        left.spin(forward);
    } else {
        left.stop();
    }
}

FlywheelPrototype::FlywheelPrototype(const motor_group& left_,
                                     const motor_group& right_,
                                     const motor_group& intake_)
    : left(left_), right(right_), intake_group(intake_) { }

void FlywheelPrototype::drive(double straightSpeed, double turnSpeed) {
    arcade_drive(straightSpeed, turnSpeed, left, right);
}

void FlywheelPrototype::intake(double intakeSpeed) {
    // Remember that the caller of our constructor has already guaranteed that,
    // when intake_group is set spinning, both flywheels are rotating in the
    // opposite direction. There is no further work on our part needed to make
    // that happen.

    if (abs(intakeSpeed) < DEADZONE) {
        intake_group.stop();
    } else {
        intake_group.spin(forward, intakeSpeed * 100, pct);
    }

}

double FlywheelPrototype::intake_speed() {
    double result = this->intake_group.velocity(percent);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("First motor velocity is %.2f  ", result);
    return result;
}


PivotRampPrototype::PivotRampPrototype(const motor_group& left_, const motor_group& right_,
                                       const motor_group& intake_, const motor_group& lift_,
                                       double rotToTop)
    : left(left_), right(right_), intake_group(intake_), lift_group(lift_),
      rotationsToTop(rotToTop) {

        // Where we are right now -- the initialLiftPosition -- will now
        // correspond to an encoder value of zero.
        lift_group.resetPosition();
}

void PivotRampPrototype::drive(double straightSpeed, double turnSpeed) {
    arcade_drive(straightSpeed, turnSpeed, left, right);
}

void PivotRampPrototype::intake(double intakeSpeed) {
    this->intake_group.setVelocity(intakeSpeed * 100, percent);
}

void PivotRampPrototype::lift(double desiredLiftPosition) {
    // Clamp the parameter of interpolation to the interval [0, 1].
    double u = max(0.0, min(desiredLiftPosition, 1.0));

    // Use linear interpolation to find the the total number of rotations needed
    // to reach the desired abstract liftRotations such as 0.6 of the way up.
    double desiredRotations = u * (rotationsToTop);

    const bool waitForCompletion = false;
    this->lift_group.spinToPosition(desiredRotations, rev,
                                    LIFT_VELOCITY_PERCENT, velocityUnits::pct,
                                    waitForCompletion);
}

void PivotRampPrototype::setLiftRotationsDebug(double liftRotations) {
    const bool waitForCompletion = false;
    this->lift_group.spinToPosition(liftRotations, rev, LIFT_VELOCITY_PERCENT,
                                    velocityUnits::pct,
                                    waitForCompletion);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Lift at %.2f (target: %d)  ", lift_group.position(rev), liftRotations);
}