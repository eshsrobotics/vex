#ifndef HARDWARE_H_INLCUDED
#define HARDWARE_H_INLCUDED

#include "vex.h"

extern vex::motor L1, L2, R1, R2;
extern vex::motor_group L, R;
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::bumper clawBumper;
extern vex::motor clawMotor;
extern vex::motor armMotorLeft;
extern vex::motor armMotorRight;
extern vex::triport tri;
extern vex::triport::port& clawBumpSensorPort;

// There are a number of broken ports on the current Brain.
// Ports that have been tested and work in isolation: 10, 18
// Ports known to be broken: 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 14, 15, 16, 17, 20
// Ports that have not yet been tested: None
// Ports that give resistance, but do not fully spin the test motor: 12, 19

const int LEFT_MOTOR_PORT_FRONT = 15;//5;
const int LEFT_MOTOR_PORT_BACK = 6;//16;
const int RIGHT_MOTOR_PORT_FRONT = 12;//7;
const int RIGHT_MOTOR_PORT_BACK = 19;//8;
const int CLAW_MOTOR_PORT = 9;
const int ARM_MOTOR_LEFT_PORT = 18;//19;
const int ARM_MOTOR_RIGHT_PORT = 17;//11;

#endif // (#ifndef HARDWARE_H_INLCUDED)