#include "vex.h"
#include "hardware.h"

using namespace vex;

brain Brain;
controller Controller = controller(primary);
// motor format: motor(port, reversed) where 'port' is an integer for the port
// number and 'reversed' is a boolean for if the motor needs to be reversed or not
motor leftFrontMotor = motor(LEFT_FRONT_MOTOR_PORT, false);
motor leftTopMotor = motor(LEFT_TOP_MOTOR_PORT, false);
motor leftBackMotor = motor(LEFT_BACK_MOTOR_PORT, false);
motor rightFrontMotor = motor(RIGHT_FRONT_MOTOR_PORT, true);
motor rightTopMotor = motor(RIGHT_TOP_MOTOR_PORT, true);
motor rightBackMotor = motor(RIGHT_BACK_MOTOR_PORT, true);
motor rollerMotor = motor(ROLLER_MOTOR_PORT, true);
motor_group leftMotors = motor_group(leftFrontMotor, leftTopMotor, leftBackMotor);
motor_group rightMotors = motor_group(rightFrontMotor, rightTopMotor, rightBackMotor);
