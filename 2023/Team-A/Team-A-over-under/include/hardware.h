// HARDWARE.H: Declarations for the hardware for our competition robot.


#ifndef HARDWARE_H_IS_PRESENT
#define HARDWARE_H_IS_PRESENT

#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

const int LEFT_FRONT_MOTOR_PORT = 15-1;
const int LEFT_TOP_MOTOR_PORT = 17-1;
const int LEFT_BACK_MOTOR_PORT = 14-1;
const int RIGHT_FRONT_MOTOR_PORT = 16-1;
const int RIGHT_TOP_MOTOR_PORT = 18-1;
const int RIGHT_BACK_MOTOR_PORT = 19-1;

const int INERTIAL_SENSOR_PORT = 20-1;
const int LIFT_PORT = 10-1;
const int FLYWHEEL_PORT = 5-1;

// The distance between the centers of the left and right wheels of the robot
const double WHEEL_BASE_INCHES = 10.125;

// Still need to calculate
const double WHEEL_GEAR_RATIO = 1.0;

const double WHEEL_DIAMETER = 3.25;
const double WHEEL_CIRCUMFERENCE = 10.2101761242;

const double PI = 3.14159265359;

const int DEADZONE = 5;

const int DEGREES_FOR_LIFT_UP = 100;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::motor leftFrontMotor;
extern vex::motor leftTopMotor;
extern vex::motor leftBackMotor;
extern vex::motor rightFrontMotor;
extern vex::motor rightTopMotor;
extern vex::motor rightBackMotor;
extern vex::motor_group leftMotors;
extern vex::motor_group rightMotors;
extern vex::inertial inertialSensor;
extern vex::motor liftMotor;
extern vex::motor flywheelMotor;
extern digital_out winglet;
extern digital_out climbingHook;

#endif // (#ifndef HARDWARE_H_IS_PRESENT)