#include "hardware.h"
#include <cmath>
#include <algorithm>
using std::min;
using std::max;

/**
 * This refers to the number of rotations from the odometry wheel from the last
 * time we called the drive function.
 */
double previousRotations = 0; 

double xPosition = 0;
double yPosition = 0;



vex::brain brain;
vex::controller controller;

vex::motor leftMotor1(leftFrontPort);
vex::motor leftMotor2(leftTopPort);
vex::motor leftMotor3(leftBottomPort);
vex::motor_group leftMotorGroup(leftMotor1, leftMotor2, leftMotor3);

vex::motor rightMotor1(rightFrontPort);
vex::motor rightMotor2(rightTopPort);
vex::motor rightMotor3(rightBottomPort);
vex::motor_group rightMotorGroup(rightMotor1, rightMotor2, rightMotor3);

vex::rotation odometrySensor(odometrySensorPort);

vex::inertial inertialSensor(inertialPort);

void drive(double driveForward, double turnClockwise) {
    double currentRotations = odometrySensor.position(vex::rotationUnits::rev);

    double distanceTraveledInches = (currentRotations - previousRotations) * rotationsToDistanceInches;

    // If we rotate counterclockwise, then our angle increases. For this reason,
    // we need to convert our rotation value to a counterclockwise angle. Thus,
    // we keep the heading angle between 0 and 360 degrees.
    double correctedHeading = 360 - inertialSensor.heading(vex::degrees);

    double deltaXInches = distanceTraveledInches * std::cos(correctedHeading);
    double deltaYInches = distanceTraveledInches * std::sin(correctedHeading);

    xPosition = xPosition + deltaXInches;
    yPosition = yPosition + deltaYInches;

    double leftSpeed = driveForward + turnClockwise;
    
    leftSpeed = min(100.0, max(-100.0, leftSpeed));
    if (fabs(leftSpeed) < DEADZONE_PCT) {
        leftSpeed = 0;
    }
    double rightSpeed = driveForward - turnClockwise;

    rightSpeed = min(100.0, max(-100.0, rightSpeed));

    if (fabs(rightSpeed) < DEADZONE_PCT) {
        rightSpeed = 0;
    }

    previousRotations = currentRotations;
}

void getRelativePosition(double& xPositionInches, double& yPositionInches) {
    xPositionInches = xPosition;
    yPositionInches = yPosition;
}

void resetRelativePosition() {
    xPosition = 0;
    yPosition = 0;
}
