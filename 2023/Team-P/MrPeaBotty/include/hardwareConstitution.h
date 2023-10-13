#ifndef HARDWARE_H_INLCUDED
#define HARDWARE_H_INLCUDED

#include "vex.h"

extern vex::motor L1, L2, R1, R2;
extern vex::motor_group L, R;
extern vex::brain Brain;
extern vex::controller Controller;

const int LEFT_MOTOR_PORT_A = 5;
const int LEFT_MOTOR_PORT_B = 6;
const int RIGHT_MOTOR_PORT_A = 7;
const int RIGHT_MOTOR_PORT_B = 8;

#endif // (#ifndef HARDWARE_H_INLCUDED)