// PROTOTYPES.CPP -- Implementation file for PROTOTYPE.H
#include <algorithm>    // min, max, for_each
#include <sstream>      // stringstream
#include <iomanip>      // setprecision
#include "prototypes.h"
#include "robot-config.h"

using std::min;
using std::max;
using std::vector;
using std::for_each;
using std::stringstream;
using std::setprecision;
using namespace vex;

/**
 * Internal helper function for differential driving with arcade-style controls.
 */
void arcade_drive(double straightSpeed, double turnSpeed, vector<motor>& left,
                  vector<motor>& right) {

    // We do not want any minor mis-inputs to throw the robot off-course.
    if (fabs(straightSpeed) < DEADZONE) {
        straightSpeed = 0;
    }
    if (fabs(turnSpeed) < DEADZONE) {
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
    double leftVelocity = -(sum);
    double rightVelocity =-(difference);
    leftVelocity *= 0.3;
    rightVelocity *= 0.3;

    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("Vel: l=%.2f, r=%.2f  ", leftVelocity, rightVelocity);

    if (rightVelocity != 0) {
        int index = 0;
        for_each(right.begin(), right.end(), [&](motor& m) {
            if (index >= 0) {
                m.setVelocity(rightVelocity * 100, percent);
                m.spin(forward);
            }
            index++;
        });        
        // right.setVelocity(rightVelocity * 100, percent);
        // right.spin(forward);
    } else {
        for_each(right.begin(), right.end(), [&](motor& m) {
            m.stop();
        });
        // right.stop();
    }

    if (leftVelocity != 0) {
        for_each(left.begin(), left.end(), [&](motor& m) {
            m.setVelocity(leftVelocity * 100, percent);
            m.spin(forward);
        });
        // left.setVelocity(leftVelocity * 100, percent);
        //left.spin(forward);
    } else {
        for_each(left.begin(), left.end(), [&](motor& m) {
            m.stop();
        }); 
        // left.stop();               
    }
}

FlywheelPrototype::FlywheelPrototype(const motor_group& left_,
                                     const motor_group& right_,
                                     const motor_group& intake_)
    : left(left_), right(right_), intake_group(intake_) { }

void FlywheelPrototype::drive(double straightSpeed, double turnSpeed) {
    // arcade_drive(straightSpeed, turnSpeed, left_motors, right_motors);
}

void FlywheelPrototype::intake(double intakeSpeed) {
    // Remember that the caller of our constructor has already guaranteed that,
    // when intake_group is set spinning, both flywheels are rotating in the
    // opposite direction. There is no further work on our part needed to make
    // that happen.

    if (fabs(intakeSpeed) < DEADZONE) {
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
    : intake_group(intake_), lift_group(lift_),
      rotationsToTop(rotToTop) {

    // Where we are right now -- the initialLiftPosition -- will now
    // correspond to an encoder value of zero.
    lift_group.resetPosition();
}

PivotRampPrototype::PivotRampPrototype(const std::vector<vex::motor>& left_motors_,
                                       const std::vector<vex::motor>& right_motors_,
                                       const vex::motor_group& intake_, const vex::motor_group& lift_,
                                       double rotToTop) 
    : left_motors(left_motors_), right_motors(right_motors_),
      intake_group(intake_), lift_group(lift_), rotationsToTop(rotToTop) {
    // Where we are right now -- the initialLiftPosition -- will now
    // correspond to an encoder value of zero.
    lift_group.resetPosition();
}

void PivotRampPrototype::drive(double straightSpeed, double turnSpeed) {
    arcade_drive(straightSpeed, turnSpeed, left_motors, right_motors);
}

void PivotRampPrototype::intake(double intakeSpeed) {
    this->intake_group.setVelocity(intakeSpeed * 100, percent);
    this->intake_group.spin(forward);
}

void PivotRampPrototype::setLiftPosition(double desiredLiftPosition) {
    // Clamp the parameter of interpolation to the interval [0, 1].
    double u = max(0.0, min(desiredLiftPosition, 1.0));

    // Use linear interpolation to find the the total number of rotations needed
    // to reach the desired abstract liftRotations such as 0.6 of the way up.
    double desiredRotations = u * (rotationsToTop);

    const bool waitForCompletion = false;
    this->lift_group.spinToPosition(desiredRotations, rev,
                                    LIFT_VELOCITY_PERCENT, velocityUnits::pct,
                                    waitForCompletion);

    Controller.Screen.setCursor(CONTROLLER_LIFT_POSITION_ROW, 1);
    Controller.Screen.print("Lift=%.2f%, target=%.2f%  ", getliftPosition() * 100, desiredLiftPosition * 100);
}

double PivotRampPrototype::getliftPosition() const {
    motor_group lift_gr = this->lift_group;
    double rotations = lift_gr.position(vex::rotationUnits::rev);

    return rotations/rotationsToTop;
}

void PivotRampPrototype::moveLiftDirect(double rotations) {
    if (fabs(rotations) < DEADZONE) {
        this->lift_group.stop();
    } else {
        const bool waitForCompletion = false;
        this->lift_group.spinFor(rotations, vex::rotationUnits::rev, waitForCompletion);

        Controller.Screen.setCursor(CONTROLLER_LIFT_POSITION_ROW, 1);
        Controller.Screen.print("Lift at %.2f revs ",
                                lift_group.position(rev));
    }
}

void PivotRampPrototype::setLiftHeights(LiftHeights liftHeights) {
    liftHeights_ = liftHeights;
}