#include "hardwareConstitution.h"

vex::motor L1(LEFT_MOTOR_PORT_A);
vex::motor L2(LEFT_MOTOR_PORT_B);
vex::motor R1(RIGHT_MOTOR_PORT_A);
vex::motor R2(RIGHT_MOTOR_PORT_B);

vex::motor_group L(L1, L2);
vex::motor_group R(R1, R2);

vex::brain Brain;

vex::controller Controller(vex::controllerType::primary);