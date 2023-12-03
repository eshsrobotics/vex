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

const int LEFT_MOTOR_PORT_FRONT = 5;
const int LEFT_MOTOR_PORT_BACK = 6;
const int RIGHT_MOTOR_PORT_FRONT = 7;
const int RIGHT_MOTOR_PORT_BACK = 8;
const int CLAW_MOTOR_PORT = 9;
const int ARM_MOTOR_LEFT_PORT = 19;
const int ARM_MOTOR_RIGHT_PORT = 11;

//Port 20 and 10 are bad.
#endif // (#ifndef HARDWARE_H_INLCUDED)