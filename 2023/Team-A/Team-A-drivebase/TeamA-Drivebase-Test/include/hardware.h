#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

const int LEFT_FRONT_MOTOR_PORT = 1-1;
const int LEFT_TOP_MOTOR_PORT = 2-1;
const int LEFT_BACK_MOTOR_PORT = 3-1;
const int RIGHT_FRONT_MOTOR_PORT = 11-1;
const int RIGHT_TOP_MOTOR_PORT = 12-1;
const int RIGHT_BACK_MOTOR_PORT = 13-1;

// Don't know actual values
const double WHEEL_TRAVEL = 320.0;
const double TRACK_WIDTH = 320.0;
const double WHEEL_BASE = 130.0;

const double WHEEL_GEAR_RATIO = 1.0;

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

void vexcodeInit(void);