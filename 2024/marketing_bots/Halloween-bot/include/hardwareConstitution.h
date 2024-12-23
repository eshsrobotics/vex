#ifndef HARDWARE_H_INLCUDED
#define HARDWARE_H_INLCUDED

#include "vex.h"

extern vex::motor L1, L2, R1, R2;
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::bumper clawBumper;
extern vex::motor clawMotor;
extern vex::motor armMotorLeft;
extern vex::motor armMotorRight;

// Use lazy initialization for the bump sensor.
//
// Why?  Because we have a dependency problem: the bumper depends on a
// three-wire port in order to be constructed, but the Brain has the only valid
// three-wire port.  Therefore the bumper MUST be constructed after the Brain.
// The only times this function will be called are during teleop and during
// pre_auton(), both of which occur AFTER main() starts, so the Brain will have
// already been constructed by then.
vex::bumper& getBumper();

// On the Brain given to us by 6526, the following ports are marked as dead:
// 6, 7?, 9, 10, 16, 17, 20?
// These ports seem loose: 2, 3, 13, 18
const int LEFT_MOTOR_PORT_FRONT = 11 - 1;
const int LEFT_MOTOR_PORT_BACK = 12 - 1; // OK
const int RIGHT_MOTOR_PORT_FRONT = 13 - 1;
const int RIGHT_MOTOR_PORT_BACK = 14 - 1;
const int CLAW_MOTOR_PORT = 15 - 1;
const int ARM_MOTOR_LEFT_PORT = 16 - 1;
const int ARM_MOTOR_RIGHT_PORT = 17 - 1; // OK

#endif // (#ifndef HARDWARE_H_INLCUDED)