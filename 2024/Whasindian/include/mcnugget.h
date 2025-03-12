#ifndef MCNUGGET_H
#define MCNUGGET_H

#include "vex.h"

extern vex::brain Brain;
extern vex::controller Controller;

// The motor port assignments below are just place-holders and are subject to change
// The first number is what port you should connect the motor to in real life.
// The "- 1" is added because each motor port is offset by 1 in the software.
const int LEFT_FRONT_PORT = 1 - 1;
const int LEFT_MIDDLE_PORT = 2 - 1;
const int LEFT_BACK_PORT = 3 - 1;

const int RIGHT_FRONT_PORT = 4 - 1;
const int RIGHT_MIDDLE_PORT = 5 - 1;
const int RIGHT_BACK_PORT = 6 - 1;


extern vex::motor LeftFront;
extern vex::motor LeftMiddle;
extern vex::motor LeftBack;
extern vex::motor RightFront;
extern vex::motor RightMiddle;
extern vex::motor RightBack;

extern vex::motor_group Left;
extern vex::motor_group Right;

void letHimCook(double frontBackSpeed, double turnSpeed);

#endif