#ifndef HARDWARE_H_INLCUDED
#define HARDWARE_H_INLCUDED

#include "vex.h"

extern vex::motor L1, L2, R1, R2;
extern vex::motor_group L, R;
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::bumper clawBumper;
extern vex::motor clawMotor;
extern vex::motor armMotor;

const int LEFT_MOTOR_PORT_FRONT = 5;
const int LEFT_MOTOR_PORT_BACK = 6;
const int RIGHT_MOTOR_PORT_FRONT = 7;
const int RIGHT_MOTOR_PORT_BACK = 8;
const int CLAW_MOTOR_PORT = 9;
const int ARM_MOTOR_PORT = 10;

vex::triport tri;
vex::triport::port& clawBumpSensorPort = tri.A;

#endif // (#ifndef HARDWARE_H_INLCUDED)