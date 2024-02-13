#include "hardwareConstitution.h"

using namespace vex;

motor L1(LEFT_MOTOR_PORT_FRONT, true);
motor L2(LEFT_MOTOR_PORT_BACK, true);
motor R1(RIGHT_MOTOR_PORT_FRONT);
motor R2(RIGHT_MOTOR_PORT_BACK);
motor_group Left(L1, L2);
motor_group Right(R1, R2);
motor armMotorLeft(ARM_MOTOR_LEFT_PORT);
motor armMotorRight(ARM_MOTOR_RIGHT_PORT);
motor clawMotor(CLAW_MOTOR_PORT, true);
brain Brain;

bumper& getBumper() {
    static bumper b(Brain.ThreeWirePort.A);
    return b;
}

controller Controller(controllerType::primary);
