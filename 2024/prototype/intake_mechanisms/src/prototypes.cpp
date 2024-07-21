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

PivotRampPrototype::PivotRampPrototype(motor_group& left_, motor_group& right_,
                                       motor_group& intake_, motor_group& lift_,
                                       double rotToTop)
    : left(left_), right(right_), intake_group(intake_), lift_group(lift_), 
      rotationsToTop(rotToTop) {

        // Where we are right now -- the initialLiftPosition -- will now
        // correspond to an encoder value of zero.
        lift_group.resetPosition();
}

void PivotRampPrototype::drive(double straightSpeed, double turnSpeed) {
    //This is an arcade drive formula translation. We want to ensure that the
    // actual speed that were are passing into setVelocity is a value between 1
    // and -1.

    // Clamp the input to the interval [-1, 1].
    double sum = straightSpeed + turnSpeed;
    double difference = straightSpeed - turnSpeed;
    sum = max(-1.0, min(sum, 1.0));
    difference = max(-1.0, min(difference, 1.0));

    this->left.setVelocity(-(sum) * 100, percent);
    this->right.setVelocity(-(difference) * 100, percent);
    left.spin(forward);
    right.spin(forward);

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

    stringstream out;
    out << "Lift at " << setprecision(2) << lift_group.position(rev)
        << " (target: " << liftRotations << ")  ";
    Brain.Screen.setCursor(1, 1);
}