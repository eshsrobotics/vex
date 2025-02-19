// hardware.h: Contains declarations for the vex hardware on our robot

#ifndef HARDWARE_H
#define HARDWARE_H

#include "vex.h"

extern vex::brain Brain;
extern vex::controller Controller;

// Drive motor ports.
// The first number is what port you should connect the motor to in real life.
// The "- 1" is added because each motor port is offset by 1 in the software.
const int FRONT_LEFT_PORT = 4 - 1;
const int FRONT_RIGHT_PORT = 5 - 1;
const int BACK_LEFT_PORT = 6 - 1;
const int BACK_RIGHT_PORT = 7 - 1;

const double JOYSTICK_DEADZONE = 0.1;
const bool ACCELERATION_ENABLED = true;
const double FORWARD_BACK_ACCELERATION = 0.03;

// The robot runs at 50Hz.
//
// If, when the joystick is idle, you want the robot to take *less* than 1.0
// seconds to  decelerate to the deadzone, decrease this value.  To make the
// robot take *more* than 1.0 seconds to decelerate, increase this value
// instead.
const double FRAMES_TO_DECELERATE = 160.0;

// This decay factor will cause us to decelerate from full speed to the deadzone
// within FRAMES_TO_DECELERATE frames.
//
// You can confirm this by calculating pow(DECAY_FACTOR, FRAMES_TO_DECELERATE)
// and confirming that this value is equal to the deadzone.
const double DECAY_FACTOR = exp(log(JOYSTICK_DEADZONE) / FRAMES_TO_DECELERATE); 

// The drive motors (2 motors on each side of the drive base.)
extern vex::motor FrontLeft;
extern vex::motor FrontRight;
extern vex::motor BackLeft;
extern vex::motor BackRight;

// The intake motor, used to collect rings.
extern vex::motor Intake;

// The clamp motor, used to hold mobile goals.
extern vex::motor Clamp;

// Limit switch to stop clamp from opening too far.
extern vex::limit ClampLimit;

const int CLAMP_PORT = 11 - 1;

// const double CLAMP_TIMEOUT_SEC = 0.40;

// The clamp timeout variable needed to be split into two variables since the
// clamp was closer to the ground than expected, and even if we lowered the
// timeout time the clamp kept pushing into the ground. Because of this, the
// timeout time when the clamp is going downwards is lower than when the clamp
// is moving upwards.
const double OPEN_CLAMP_TIMEOUT_SEC = 0.40;

const double CLOSE_CLAMP_TIMEOUT_SEC = 0.40;

const double CLAMP_VELOCITY_PCT = 100.00;

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
const double DRIVE_TRAIN_GEAR_RATIO = 1.0; // Ratio between motor input shaft and wheel output shaft

extern vex::drivetrain DriveTrain;


/**
 * Controls the drive subsystem by instantaneously adjusting the speed of the
 * drive motors.
 *
 * By having this as a separate function, we can call the same *tested* code in
 * both teleop and autonomous, and both will do the same thing to the drive.
 *
 * @param frontBackSpeed The speed in the forward or backward direction from 
 *                       -100 (full speed backwards) to +100 (full speed
 *                       forwards). Use 0 if turning is not desired.
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
 * Controls the lift subsystem. We can call this during teleop and autonomous.
 *
 * @param lift Makes the Lift raise and lower pivot ramp. If the sign of the
 *             number is a positive, it triggers the lift to go up. Zero stops
 *             the system, and if the sign of the number is negative it triggers
 *             lowering system.
 */
void robotlift(int lift);

/**
 * Controls the robot clamp. The function needs to be called once per frame
 * (both during teleop *and* during autonomous) because, if not called, then the
 * clamp motor will continue whatever it was told last forever. 
 *
 * By calling this function once per frame the clamp motors velocity can be
 * continuously managed.
 *
 * @param close Makes the clamp open or close. If the argument is true, the
 *              clamp will close. If the argument is false, the clamp will open.
 */
void updateClampState(bool close);


#endif