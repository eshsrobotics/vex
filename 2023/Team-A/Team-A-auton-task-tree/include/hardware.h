#ifndef HARDWARE_H_IS_PRESENT
#define HARDWARE_H_IS_PRESENT

#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

const int LEFT_FRONT_MOTOR_PORT = 1-1;
const int LEFT_TOP_MOTOR_PORT = 2-1;
const int LEFT_BACK_MOTOR_PORT = 3-1;
const int RIGHT_FRONT_MOTOR_PORT = 11-1;
const int RIGHT_TOP_MOTOR_PORT = 12-1;
const int RIGHT_BACK_MOTOR_PORT = 13-1;

const int INERTIAL_SENSOR_PORT = 4-1;

// Don't know actual value (this is the distance between the centers of the left and right wheels)
const double WHEEL_BASE = 130.0;

// Still need to calculate
const double WHEEL_GEAR_RATIO = 1.0;

const double WHEEL_DIAMETER = 3.25;
const double WHEEL_CIRCUMFERENCE = 10.2101761242;

const double PI = 3.14159265359;

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

void vexcodeInit(void);
#endif // (#ifndef HARDWARE_H_IS_PRESENT)