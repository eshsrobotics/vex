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

void intake(double intakeSpeed, vector<motor>& intake_motors) {
    if (fabs(intakeSpeed) < INTAKE_SPEED_DEADZONE) {
        for_each(intake_motors.begin(), intake_motors.end(), [](motor& intake_motor) {
            intake_motor.stop();
        });
    } else {
        for_each(intake_motors.begin(), intake_motors.end(), [intakeSpeed](motor& intake_motor) {
            intake_motor.spin(forward, intakeSpeed * 100, pct);
        });
    }
}

/**
 * Internal helper function for differential driving with arcade-style controls.
 */
void arcade_drive(double straightSpeed, double turnSpeed, vector<motor>& left,
                  vector<motor>& right) {
    double JOYSTICK_DEADZONE = 0.05;
    // We do not want any minor mis-inputs to throw the robot off-course.
    if (fabs(straightSpeed) < JOYSTICK_DEADZONE) {
        straightSpeed = 0;
    }
    if (fabs(turnSpeed) < JOYSTICK_DEADZONE) {
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
    double rightVelocity = -(difference);
    leftVelocity *= 1;
    rightVelocity *= 1;

    Controller.Screen.setCursor(3, 1);
    //Controller.Screen.print("Vel: l=%.2f, r=%.2f  ", leftVelocity, rightVelocity);

    if (rightVelocity != 0) {
        for_each(right.begin(), right.end(), [&](motor& m) {
            m.setVelocity(rightVelocity * 100, percent);
            m.spin(reverse);
        });
    } else {
        for_each(right.begin(), right.end(), [&](motor& m) {
            m.stop();
        });
    }

    if (leftVelocity != 0) {
        for_each(left.begin(), left.end(), [&](motor& m) {
            m.setVelocity(leftVelocity * 100, percent);
            m.spin(forward);
        });
    } else {
        for_each(left.begin(), left.end(), [&](motor& m) {
            m.stop();
        });
    }
}

/****************************************************************************
 * Definitions for the Pivot Ramp Prototype.                                *
 *                                                                          *
 * As it turns out, a lot of robots that have an Idrive, an Ilift, *and* an *
 * Iintake will look a whole lot like PivotRampPrototype.                   *
 ****************************************************************************/


PivotRampPrototype::PivotRampPrototype(const std::vector<vex::motor>& left_motors_,
                                       const std::vector<vex::motor>& right_motors_,
                                       const std::vector<vex::motor>& intake_, const std::vector<vex::motor>& lift_,
                                       double rotToTop, const vex::digital_out& pneumaticClamp_, 
                                       const vex::digital_out& pneumaticClimb_, const vex::limit& limitSwitch_)
    : left_motors(left_motors_), right_motors(right_motors_),
      intake_motors(intake_), lift_motors(lift_), rotationsToTop(rotToTop), pneumaticClamp(pneumaticClamp_), 
      pneumaticClimb(pneumaticClimb_), limitSwitch(limitSwitch_) {
    // Where we are right now -- the initialLiftPosition -- will now
    // correspond to an encoder value of zero.
    for_each(lift_motors.begin(), lift_motors.end(), [](motor& current_motor) {
        current_motor.resetPosition();
    });
}

void PivotRampPrototype::drive(double straightSpeed, double turnSpeed) {
    arcade_drive(straightSpeed, turnSpeed, left_motors, right_motors);
}

void PivotRampPrototype::resetEncoders() {
    for (unsigned int i = 0; i < left_motors.size(); i++) {
        this->left_motors[i].resetPosition();
    }
    for (unsigned int i = 0; i < right_motors.size(); i++) {
        this->right_motors[i].resetPosition();
    }
}

double PivotRampPrototype::getRotations() const {
    // We are "cheating" here. The previous version of the code we had looked
    // like this:
    //
    //   return this->left_motors[0].position(vex::rotationUnits::rev);
    //
    // but it didn't work because _unfortunately_, vex::motor::position() is a
    // non-const function.  (Why, VEX?  Why?)  Since we *know* it's not going to
    // actually change anything, we know it's safe to call even here in a const
    // method.  So we essentially tell the compiler to shove off.
    //
    // Additionally, the motor represented by left_motors[0] moves backwards
    // compared to the robot's actual movement, so currentRotations in
    // TestDriveTask always increases in the negative direction. We need to
    // multiply it by -1 to make currentRotations actually increase positively.
    
    const auto rotations = const_cast<PivotRampPrototype*>(this)->left_motors[0].position(vex::rotationUnits::rev);
    return -1 * rotations;
}

void PivotRampPrototype::intake(double intakeSpeed) {
    ::intake(intakeSpeed, intake_motors);
}

void PivotRampPrototype::setLiftPosition(double desiredLiftPosition) {
    if (!isLiftAvailable()) {
        return;
    }
    // Clamp the parameter of interpolation to the interval [0, 1].
    double u = max(0.0, min(desiredLiftPosition, 1.0));

    // Use linear interpolation to find the the total number of rotations needed
    // to reach the desired abstract liftRotations such as 0.6 of the way up.
    double desiredRotations = u * (rotationsToTop);

    // Makes the spinToPosition call non-blocking.
    const bool waitForCompletion = false;

    for (motor& current_motor : lift_motors) {
        current_motor.spinToPosition(desiredRotations, rev,
                                    LIFT_VELOCITY_PERCENT, velocityUnits::pct,
                                    waitForCompletion);
    }

    Controller.Screen.setCursor(CONTROLLER_LIFT_POSITION_ROW, 1);
    Controller.Screen.print("Lift=%.2f%, target=%.2f%  ", getliftPosition() * 100, desiredLiftPosition * 100);
}

double PivotRampPrototype::getliftPosition() const {
    if (!isLiftAvailable()) {
        return 0;
    }

    // We trying to call position which is non-const for unknown reasons so we
    // are telling the compiler to ignore the constness.
    PivotRampPrototype* that = const_cast<PivotRampPrototype*>(this);
    double rotations = that->lift_motors[0].position(rev);

    return rotations/rotationsToTop;
}

void PivotRampPrototype::moveLiftDirect(double rotations) {
    if (!isLiftAvailable()) {
        return;
    }
    // The deadzone for moving the lift without the abstraction paradigm, in
    // other words, directly. If the rotation argument is less than the
    // DEADZONE, then we won't spin at all.
    const double DEADZONE = 0.1;
    if (fabs(rotations) < DEADZONE) {
        for_each(lift_motors.begin(), lift_motors.end(), [](motor& current_motor) {
            current_motor.stop(hold);
        });
    } else {

        // Prevents the called the method from being a blocking call.
        const bool waitForCompletion = false;

        for_each(lift_motors.begin(), lift_motors.end(), [rotations](motor& current_motor) {
             current_motor.spinFor(rotations, vex::rotationUnits::rev, waitForCompletion);
        });
        //lift_motors.at(0).spinFor(rotations, vex::rotationUnits::rev, waitForCompletion);

    }
}

bool PivotRampPrototype::isLiftSpinning() const {
    bool result = false;
    PivotRampPrototype* that = const_cast<PivotRampPrototype*>(this);
    for_each(that->lift_motors.begin(), that->lift_motors.end(), [&result](motor& current_motor) {
        if (current_motor.isSpinning()) {
            result = true;
        }
    });
    return result;
}

void PivotRampPrototype::setLiftHeights(LiftHeights liftHeights) {
    if (!isLiftAvailable()) {
        return;
    }
    liftHeights_ = liftHeights;
}

bool PivotRampPrototype::isLiftAvailable() const {
    return !lift_motors.empty();
}

bool PivotRampPrototype::hasLiftReachedBottom() const {
    PivotRampPrototype* that = const_cast<PivotRampPrototype*>(this);
    int limitSwitchValue = that->limitSwitch.value();
    //vex::limit input(Seventeen59A.ThreeWirePort.B);
    return limitSwitchValue;
}

void PivotRampPrototype::clamp(bool active) {
    this->pneumaticClamp.set(active);
}

void PivotRampPrototype::activateClimb() {
    this->pneumaticClimb.set(true);
}