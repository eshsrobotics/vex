#ifndef MCNUGGET_H
#define MCNUGGET_H

#include "vex.h"

extern vex::brain NuggetMind;
extern vex::controller Spatula;

// The motor port assignments below are just place-holders and are subject to change
// The first number is what port number you should connect the motor to in real life.
// The "- 1" is added because each motor port is offset by 1 in the software.
// For example: If it says PORT = 17 - 1, connect the motor to port 17 in real life.
const int LEFT_FRONT_PORT = 1 - 1;
const int LEFT_BACK_TOP_PORT = 2 - 1;
const int LEFT_BACK_PORT = 3 - 1;

const int RIGHT_FRONT_PORT = 4 - 1;
const int RIGHT_BACK_TOP_PORT = 5 - 1;
const int RIGHT_BACK_PORT = 6 - 1;

extern vex::motor LeftFront;
extern vex::motor LeftBackTop;
extern vex::motor LeftBack;
extern vex::motor RightFront;
extern vex::motor RightBackTop;
extern vex::motor RightBack;

extern vex::motor_group Left;
extern vex::motor_group Right;

void letHimCook(double leftNuggetSpeed, double rightNuggetSpeed);

#endif