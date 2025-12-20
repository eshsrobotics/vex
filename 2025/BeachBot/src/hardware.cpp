#include "hardware.h"
#include "vex.h"
#include <algorithm>
#include <memory>
#include <iostream>

using std::max;
using std::min;
using std::unique_ptr;

vex::brain Brain;

// This array has a size that depends on the number of motors in our
// differential drive. We have a choice between allocating static ports (that
// never change) for the rest of our subsystems or building off of the drive
// motor port assignments.  Of the two, we prefer having fixed ports for
// non-drive motors.
//
// Keep in mind that this means our additional ports should start beyond the
// last possible port number that any differential drive could have.  So we
// start with vex::PORT9.
std::vector<vex::motor> driveMotors; 

vex::motor leftIntakeMotor(vex::PORT9, true);
vex::motor rightIntakeMotor(vex::PORT10);
vex::motor uptakeMotor(vex::PORT11);

vex::motor armLeft(vex::PORT14);
vex::motor armRight(vex::PORT13, true);
vex::motor descoreArm(vex::PORT15, true);

void createDriveMotors(std::vector<int> driveMotorPorts) {

    size_t numberOfMotorPorts = driveMotorPorts.size();

    for (size_t i = 0; i < numberOfMotorPorts; i++) {

        // If we encounter a negative port number, then that means we need to
        // reverse the corresponding motor when constructing it.
        vex::motor motor = vex::motor(abs(driveMotorPorts[i]),
                                      driveMotorPorts[i] > 0 ? false : true);

        driveMotors.emplace_back(motor);
    } 

}

void drive(double frontBackSpeed, double turnSpeed) {

    size_t numberOfMotors = driveMotors.size();

    double leftMotorSpeed = (frontBackSpeed + turnSpeed);
    double rightMotorSpeed = (frontBackSpeed - turnSpeed);
    leftMotorSpeed = max(-100.0, min(leftMotorSpeed, 100.0));
    rightMotorSpeed = max(-100.0, min(rightMotorSpeed, 100.0));

    // Drive or stop the motors on the left side.
    for (size_t i = 0; i < numberOfMotors/2; i++) {
        if(fabs(leftMotorSpeed) > DEADZONE) {
            driveMotors[i].spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
        } else {
            driveMotors[i].stop(vex::brakeType::brake);
        }
    }

    // Drive or stop the motors on the right side.
    for (size_t i = numberOfMotors/2; i < numberOfMotors; i++) {


        if(fabs(rightMotorSpeed) > DEADZONE) {
            driveMotors[i].spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);
        } else {
            driveMotors[i].stop(vex::brakeType::brake);
        }
    }
}

void intakeControl(int speedPercent) {
    if (speedPercent == 0) {
        // Stop the intake motors.
        leftIntakeMotor.stop(vex::brakeType::brake);
        rightIntakeMotor.stop(vex::brakeType::brake);
        uptakeMotor.stop(vex::brakeType::brake);
    } else {
        leftIntakeMotor.spin(vex::forward, speedPercent, vex::percentUnits::pct);
        rightIntakeMotor.spin(vex::forward, speedPercent, vex::percentUnits::pct);
        uptakeMotor.spin(vex::forward, speedPercent, vex::percentUnits::pct);
    }
}

void armControl(int speedPercent) {
    if (speedPercent == 0) {
        // Stop arm motors
        armLeft.stop(vex::brakeType::hold);
        armRight.stop(vex::brakeType::hold);
    } else {
        armLeft.spin(vex::forward, speedPercent, vex::percentUnits::pct);
        armRight.spin(vex::forward, speedPercent, vex::percentUnits::pct);
    }
}

void descoreControl(int descorePercent) {
    if (descorePercent == 0) {
        descoreArm.stop(vex::brakeType::hold);
    } else {
        descoreArm.spin(vex::forward, descorePercent, vex::percentUnits::pct);
    }
}

void testMotors(int timeInMillis) {

    while (true) {

        for (size_t i = 0; i < driveMotors.size(); i++) {

            driveMotors[i].spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
            wait(timeInMillis, vex::msec);
            driveMotors[i].stop(vex::brakeType::brake);

        }

    }

}

