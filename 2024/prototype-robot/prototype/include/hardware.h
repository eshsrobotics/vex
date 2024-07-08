// HARDWARE.H: Declarations for the hardware for our competition robot.


#ifndef HARDWARE_H_IS_PRESENT
#define HARDWARE_H_IS_PRESENT

#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

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
extern vex::motor rollerMotor;


const int LEFT_FRONT_MOTOR_PORT = 15-1;
const int LEFT_TOP_MOTOR_PORT = 17-1;
const int LEFT_BACK_MOTOR_PORT = 14-1;
const int RIGHT_FRONT_MOTOR_PORT = 16-1;
const int RIGHT_TOP_MOTOR_PORT = 18-1;
const int RIGHT_BACK_MOTOR_PORT = 19-1;
const int ROLLER_MOTOR_PORT = 13-1;

const int DEADZONE = 5;

#endif // (#ifndef HARDWARE_H_IS_PRESENT)