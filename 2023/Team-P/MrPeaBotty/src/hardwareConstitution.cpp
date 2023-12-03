#include "hardwareConstitution.h"

vex::motor L1(LEFT_MOTOR_PORT_FRONT);
vex::motor L2(LEFT_MOTOR_PORT_BACK);
vex::motor R1(RIGHT_MOTOR_PORT_FRONT);
vex::motor R2(RIGHT_MOTOR_PORT_BACK);
vex::motor armMotorLeft(ARM_MOTOR_LEFT_PORT);
vex::motor armMotorRight(ARM_MOTOR_RIGHT_PORT);
vex::motor clawMotor(CLAW_MOTOR_PORT);

vex::motor_group L(L1, L2);
vex::motor_group R(R1, R2);


vex::brain Brain;

vex::controller Controller(vex::controllerType::primary);
