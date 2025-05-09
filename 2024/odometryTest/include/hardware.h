#ifndef HARDWARE_H_INCLUDED
#define HARDWARE_H_INCLUDED
#include "vex.h"

extern vex::brain brain;
extern vex::controller controller;
extern vex::motor_group leftMotorGroup;
extern vex::motor_group rightMotorGroup;

extern vex::motor leftMotor1;
extern vex::motor leftMotor2;
extern vex::motor leftMotor3;

extern vex::motor rightMotor1;
extern vex::motor rightMotor2;
extern vex::motor rightMotor3;

const int leftFrontPort = 15-1; //the frontmost motor on the left side of the drive
const int leftTopPort = 14-1; //the motor on top at the back of the left side of the drive
const int leftBottomPort = 16-1; //the motor on bottom at the back of the left side of the drive

const int rightFrontPort = 12-1; //the frontmost motor on the right side of the drive
const int rightTopPort = 20-1; //the motor on top at the back of the right side of the drive
const int rightBottomPort = 13-1; //the motor on bottom at the back of the right side of the drive

/**
 * This is the drive function that instantaneously sets the motor speeds. This
 * function must be called multiple times if we want the robot to drive over a
 * certain prolonged period of time.
 *
 * @param driveForward This is the speed value in the forward direction clamped
 * between -100 and 100. 100 is full speed forward, 0 is stopped, and -100 is
 * full speed backward.
 *
 * @param turnClockwise This is the speed value in the turning axis clamped
 * between -100 and 100. 100 is full speed clockwise, 0 is straight/stopped, and
 * -100 is full speed counterclockwise.  
 */
void drive(double driveForward, double turnClockwise);

extern vex::rotation odometrySensor; //only used for the foward-back odometry wheel
const int odometrySensorPort = 11-1;

const double rotationsToDistanceInches = 25;

extern vex::inertial inertialSensor; //used for measuring the robot's angle
const int inertialPort = 8;

// According to https://api.vex.com/v5/home/cpp/Inertial.html, the minimum
// calibration time for an inertial sensor should be 2 seconds.
const int calibrationTimeSeconds = 3; 

/**
 * This function returns the position of the robot relative to where it first
 * started at the beginning of a match.
 *
 * @param xPositionInches[out] This parameter will be updated and changed to the
 * actual x-position relative to the left and right side of the robot since the match started.
 * 
 * @param yPositionInches[out] This parameter will be updated and changed to the
 * actual y-position relative to the front and back of the robot since the match started.
 */
void getRelativePosition(double& xPositionInches, double& yPositionInches);

void resetRelativePosition();

const double DEADZONE_PCT = 5;

#endif