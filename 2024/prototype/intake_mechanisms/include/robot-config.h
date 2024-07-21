#ifndef __ROBOT_CONFIG_INCLUDED__
#define __ROBOT_CONFIG_INCLUDED__

#include "vex.h"

using namespace vex;

extern brain Brain;
extern controller Controller;

// VEXcode devices

// The drivetrain is a class with useful member functions. For example, we can
// give the member function drivetrain() gear ratios as one of the arguments,
// which will give the code dead reckoning ability to predict how much the robot
// will move.
extern drivetrain Drivetrain;
extern motor intake_roller_motor;

const int front_left_motor_port = 2 - 1;
const int center_left_motor_port = 3 - 1;
const int back_left_motor_port = 4 - 1;
const int front_right_motor_port = 5 - 1;
const int center_right_motor_port = 6 - 1;
const int back_right_motor_port = 7 - 1;
const int intake_roller_motor_port = 8 - 1;
const auto gearbox_ratio = ratio6_1;

const double autonomous_speed_pct = 15.0;
const double autonomous_intake_speed_pct = 100;
const double experiment_duration_ms = 5000;

// How quickly to raise or lower the lift mechanism, in percent units between 0
// and 100.
const double LIFT_VELOCITY_PERCENT = 50.0;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void  vexcodeInit(void);

#endif // (ifndef __ROBOT_CONFIG_INCLUDED__)