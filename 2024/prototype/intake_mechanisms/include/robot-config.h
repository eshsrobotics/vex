#ifndef __ROBOT_CONFIG_INCLUDED__
#define __ROBOT_CONFIG_INCLUDED__

#include "vex.h"

using namespace vex;

extern brain Seventeen59A;
extern controller Controller;

// VEXcode devices

// The drivetrain is a class with useful member functions. For example, we can
// give the member function drivetrain() gear ratios as one of the arguments,
// which will give the code dead reckoning ability to predict how much the robot
// will move.
extern drivetrain Drivetrain;
extern motor intake_roller_motor;

const auto gearbox_ratio = ratio6_1;

const double autonomous_speed_pct = 15.0;

// PID Controller constants for the Turn Task.
const double TURN_TASK_P_GAIN = 0.06 * 1e-2;
const double TURN_TASK_I_GAIN = 0;
const double TURN_TASK_D_GAIN = 0;

// How quickly to raise or lower the lift mechanism, in percent units between 0
// and 100.
const double LIFT_VELOCITY_PERCENT = 50.0;

/**
* For all inputs in the range [-1, 1], the threshold that has to be overcome
* for the inputs to be considered non-zero. This currently applies to lift
* speeds, intake speeds, and driving.
*/

const int CONTROLLER_LIFT_STATE_ROW = 1;
const int CONTROLLER_LIFT_POSITION_ROW = 2;
const int CONTROLLER_ROBOT_STOPPED_ROW = 3;
const int BRAIN_CLAMP_VALUE_ROW = 5;
const int BRAIN_LIFT_POSITION_ROW = 6;

/**
 * Deadzones the intake speed velocities, meaning if they are below a certain
 * threshold, we treat it as if it were 0.
 *
 * Velocities range from [-1, 1]. Intake deadzoning is sign-independent.
 *
 * The values is arbitrarily set to 0.05 now. The value may need to be changed.
 */
const double INTAKE_SPEED_DEADZONE = 0.05;


// double LIFT_POSITION_DEADZONE = 0.05;

const double MOBILE_GOAL_INTAKE_DURATION_MILLISECONDS = 200;

/**
 * Deadzone for the TurnTask PID.
*/
const double TURN_TASK_EPSILON_DEGREES = 1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

#endif // (ifndef __ROBOT_CONFIG_INCLUDED__)
