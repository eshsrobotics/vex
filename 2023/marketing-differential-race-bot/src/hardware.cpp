#include "hardware.h"

using namespace vex;
brain Brain;
controller Controller = controller(primary);
// motor format: motor(port, reversed) where port is an integer for the port
// number and reverse is a boolean for if the motor needs to be reversed or not
motor leftMotor = motor(LEFT_MOTOR_PORT, true);
motor rightMotor = motor(RIGHT_MOTOR_PORT, false);
drivetrain drive = drivetrain(leftMotor, rightMotor, WHEEL_TRAVEL, TRACK_WIDTH, WHEEL_BASE, mm, WHEEL_GEAR_RATIO);

bool leftStop = true;
bool rightStop = true;
const int DEADZONE = 15;

int arcade_drive() {
    while (true) {
        int straightSpeed = Controller.Axis2.position();
        int turnSpeed = Controller.Axis1.position();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print(straightSpeed);
        Controller.Screen.setCursor(2,1);
        Controller.Screen.print(turnSpeed);
        Controller.Screen.clearScreen();

        if (abs(straightSpeed) < DEADZONE) {
            straightSpeed = 0;
        }

        if (abs(turnSpeed) < DEADZONE) {
            turnSpeed = 0;
        }
        if (straightSpeed != 0 || turnSpeed != 0) {
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