// PROTOTYPES.CPP -- Implementation file for PROTOTYPE.H
#include <algorithm>    // min, max
#include "prototypes.h"

using std::min;
using std::max;
using namespace vex;

PivotRampPrototype::PivotRampPrototype(motor_group& left_, motor_group& right_,
                                       motor_group& intake_, motor_group& lift_, double gr)
    : left(left_), right(right_), intake_group(intake_), lift_group(lift_), gearRatio(gr) {

}

void PivotRampPrototype::drive(double straightSpeed, double turnSpeed) {
    //This is an arcade drive formula translation. We want to ensure that the
    // actual speed that were are passing into setVelocity is a value between 1
    // and -1.

    // Clamp the input to the interval [-1, 1].
    double sum = straightSpeed + turnSpeed;
    double difference = straightSpeed - turnSpeed;
    sum = max(-1.0, min(sum, 1.0));

    this->left.setVelocity(-(straightSpeed + turnSpeed) * 100, percent);
    this->right.setVelocity(-(straightSpeed - turnSpeed) * 100, percent);
    left.spin(forward);
    right.spin(forward);

}

void PivotRampPrototype::intake(double intakeSpeed) {
    this->intake_group.setVelocity(intakeSpeed * 100, percent);

}

void PivotRampPrototype::lift(double liftPosition) {
    // Clamp the input to the interval [0, 1].
    liftPosition = max(0.0, min(liftPosition, 1.0));

    // We multiply by the gearRatio to ensure that what we passed as our
    // liftPosition is what our output gear actually does. 
    this->lift_group.setPosition(liftPosition * gearRatio, rev);
}