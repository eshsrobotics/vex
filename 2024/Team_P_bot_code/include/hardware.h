// hardware.h: Contains declarations for the vex hardware on our robot

#ifndef HARDWARE_H
#define HARDWARE_H

#include "vex.h"

extern vex::brain Brain;
extern vex::controller Controller;

// Drive motor ports.
const int FRONT_LEFT_PORT = 4 - 1;
const int FRONT_RIGHT_PORT = 5 - 1;
const int BACK_LEFT_PORT = 6 - 1;
const int BACK_RIGHT_PORT = 7 - 1;

// The drive motors (2 motors on each side of the drive base.)
extern vex::motor FrontLeft;
extern vex::motor FrontRight;
extern vex::motor BackLeft;
extern vex::motor BackRight;

// The intake motor, used to collect rings.
extern vex::motor Intake;

// Intake motor port
const int INTAKE_PORT = 8 - 1;

// Lift motor port
const int LiftFR = 9 - 1;
const int LiftBL = 10 - 1;

// These are the motor groups used to feed the vex::drivetrain object...an
// object which we are no longer convinced we need in the first place.
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
 * By having this as a separate function, we can call the same *tested* code in
 * both teleop and autonomous, and both will do the same thing to the drive.
 *
 * @param frontBackSpeed The speed in the front/back direction, from -100 (full
 *                       driving forward or backward is not desired.
 * @param turnSpeed      The angular velocity of the robot turning about its own
 *                       center, from -100 (full speed counterclockwise) to +100
 *                       (full speed clockwise.)  Use 0 if turning is not
 *                       desired.
 */
void robotDrive(double frontBackSpeed, double turnSpeed);

/**
 * Controls the intake/uptake subsystem.  We can call this both during teleop
 * and autonomous.
 *
 * @param intakeOrOuttake Makes the pivot ramp intake or eject the rings.
 *                        Positive numbers trigger intake system, zero stops the
 *                        system, and negative numbers trigger outtake system.
 */
void robotintake(int intakeOrOuttake);

/**
 * Controls the lift subsystem. We can call this during teleop and autonomus.
 *
 * @param lift Makes the Lift raise and lower pivot ramp. If the sign of the
 *             number is a positive, it triggers the lift to go up. Zero stops
 *             the system, and if the sign of the number is negative it triggers
 *             lowering system.
 */
void robotlift(int lift);

#endif