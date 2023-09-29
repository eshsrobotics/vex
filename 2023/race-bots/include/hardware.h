#include "vex.h"

const int LEFT_MOTOR_PORT = 10;
const int RIGHT_MOTOR_PORT = 11;

// Don't know actual values
const double WHEEL_TRAVEL = 320.0;
const double TRACK_WIDTH = 320.0;
const double WHEEL_BASE = 130.0;

const double WHEEL_GEAR_RATIO = 1.0;

extern brain Brain;
extern controller Controller;
extern vex::motor leftMotor;
extern vex::motor rightMotor;
extern vex::drivetrain drive;

void vexcodeInit(void);