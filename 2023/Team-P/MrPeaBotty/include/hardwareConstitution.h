#ifndef HARDWARE_H_INLCUDED
#define HARDWARE_H_INLCUDED

#include "vex.h"

extern vex::motor L1, L2, R1, R2;
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::bumper clawBumper;
extern vex::motor clawMotor;
extern vex::motor armMotorLeft;
extern vex::motor armMotorRight;
extern vex::triport tri;
extern vex::triport::port& clawBumpSensorPort;

// On the Brain given to us by 6526, the following ports are marked as dead: 
// 6, 7?, 9, 10, 16, 17, 20?
// These ports seem loose: 2, 3, 13, 18
const int LEFT_MOTOR_PORT_FRONT = 11;
const int LEFT_MOTOR_PORT_BACK = 12; // OK
const int RIGHT_MOTOR_PORT_FRONT = 13;
const int RIGHT_MOTOR_PORT_BACK = 14;
const int CLAW_MOTOR_PORT = 15;
const int ARM_MOTOR_LEFT_PORT = 16;
const int ARM_MOTOR_RIGHT_PORT = 17; // OK

#endif // (#ifndef HARDWARE_H_INLCUDED)