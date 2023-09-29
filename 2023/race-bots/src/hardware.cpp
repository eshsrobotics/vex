#include "hardware.h"

using namespace vex;
brain Brain;
controller Controller = controller(primary);
motor leftMotor = motor(LEFT_MOTOR_PORT);
motor rightMotor = motor(RIGHT_MOTOR_PORT);
drivetrain drive = drivetrain(leftMotor, rightMotor, WHEEL_TRAVEL, TRACK_WIDTH, WHEEL_BASE, mm, WHEEL_GEAR_RATIO);

bool leftStop = true;
bool rightStop = true;

int tank_drive() {
    while (true) {
        int leftSpeed = Controller.Axis3.position();
        int rightSpeed = Controller.Axis2.position();

        if (leftSpeed < 5 && leftSpeed > -5 && leftStop) {
            leftMotor.stop();
            leftStop = false;
        } else {
            leftStop = true;
        }
        if (rightSpeed < 5 && rightSpeed > -5 && rightStop) {
            rightMotor.stop();
            rightStop = false;
        } else {
            rightStop = true;
        }

        if (leftStop) {
            leftMotor.setVelocity(leftSpeed, percent);
            leftMotor.spin(forward);
        }
        if (rightStop) {
            rightMotor.setVelocity(rightSpeed, percent);
            rightMotor.spin(forward);
        }

        wait(20, msec);
    }
    return 0;
}

void vexcodeInit(void) {
    task rc_auto_loop_task_Controller(tank_drive);
}