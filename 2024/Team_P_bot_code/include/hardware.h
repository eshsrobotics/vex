// hardware.h: Contains declarations for the vex hardware on our robot

#ifndef HARDWARE_H
#define HARDWARE_H

#include "vex.h"

const int FRONT_LEFT_PORT = 4 - 1;
const int FRONT_RIGHT_PORT = 5 - 1;
const int BACK_LEFT_PORT = 6 - 1;
const int BACK_RIGHT_PORT = 7 - 1;

extern vex::brain Brain;
extern vex::controller Controller;

extern vex::motor FrontLeft;
extern vex::motor FrontRight;
extern vex::motor BackLeft;
extern vex::motor BackRight;

extern vex::motor_group Left;
extern vex::motor_group Right;

// The DRIVE_TRAIN_WIDTH_CM and DRIVE_TRAIN_LENGTH_CM don't refer to the actual length/width
// of the drivetrain, but rather the distance between the centers of the wheels

const double DRIVE_TRAIN_WIDTH_CM = 32;       // Vex calls this "track width"
const double WHEEL_CIRCUMFERENCE_CM = 30;     // Vex calls this "wheel travel"
const double DRIVE_TRAIN_LENGTH_CM = 32;      // Vex calls this "wheel base"
const double DRIVE_TRAIN_GEAR_RATIO_CM = 1.0; // Ratio between motor input shaft and wheel output shaft

extern vex::drivetrain DriveTrain;

/**
 * Controls the drive subsystem by instantaneously adjusting the speed of the
 * drive motors.
 *
 * @param frontBackSpeed The speed in the front/back direction, from -100 (full
 *                       speed backward) to +100 (full speed forward.) Use 0 if
 *                       driving forward or backward is not desired.
 * @param turnSpeed      The angular velocity of the robot turning about its own
 *                       center, from -100 (full speed counterclockwise) to +100
 *                       (full speed clockwise.)  Use 0 if turning is not
 *                       desired.
 */
void robotDrive(double frontBackSpeed, double turnSpeed);


#endif