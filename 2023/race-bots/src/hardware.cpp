#include "hardware.h"

using namespace vex;
brain Brain;
controller Controller = controller(primary);
// motor format: motor(port, reversed) where port is an integer for the port
// number and reverse is a boolean for if the motor needs to be reversed or not
motor leftMotor = motor(LEFT_MOTOR_PORT, false);
motor rightMotor = motor(RIGHT_MOTOR_PORT, true);
drivetrain drive = drivetrain(leftMotor, rightMotor, WHEEL_TRAVEL, TRACK_WIDTH, WHEEL_BASE, mm, WHEEL_GEAR_RATIO);

bool leftStop = true;
bool rightStop = true;

int tank_drive() {
    while (true) {
        int leftSpeed = Controller.Axis3.position();
        int rightSpeed = Controller.Axis2.position();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print(leftSpeed);
        Controller.Screen.setCursor(2,1);
        Controller.Screen.print(rightSpeed);
        Controller.Screen.clearScreen();


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

int arcade_drive() {
    while (true) {
        int straightSpeed = Controller.Axis2.position();
        int turnSpeed = -Controller.Axis1.position();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print(straightSpeed);
        Controller.Screen.setCursor(2,1);
        Controller.Screen.print(turnSpeed);
        Controller.Screen.clearScreen();


        if ((straightSpeed < 5 || straightSpeed > -5) || (turnSpeed < 5 || turnSpeed > -5)) {
            leftMotor.setVelocity(-(straightSpeed + turnSpeed), percent);
            rightMotor.setVelocity(-(straightSpeed - turnSpeed), percent);
            leftMotor.spin(forward);
            rightMotor.spin(forward);
        } else {
            leftMotor.stop();
            rightMotor.stop();
        }

        wait(20, msec);
    }
    return 0;
}

void vexcodeInit(void) {
    task rc_auto_loop_task_Controller(arcade_drive);
}