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
motor_group leftMotors = motor_group(leftFrontMotor, leftTopMotor, leftBackMotor);
motor_group rightMotors = motor_group(rightFrontMotor, rightTopMotor, rightBackMotor);
inertial inertialSensor = inertial(INERTIAL_SENSOR_PORT);

bool leftStop = true;
bool rightStop = true;

// TODO: Move this code back into usercontrol(), where it belongs.
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
            leftMotors.stop();
            leftStop = false;
        } else {
            leftStop = true;
        }
        if (rightSpeed < 5 && rightSpeed > -5 && rightStop) {
            rightMotors.stop();
            rightStop = false;
        } else {
            rightStop = true;
        }

        if (leftStop) {
            leftMotors.setVelocity(leftSpeed, percent);
            leftMotors.spin(forward);
        }
        if (rightStop) {
            rightMotors.setVelocity(rightSpeed, percent);
            rightMotors.spin(forward);
        }

        // Run the inertial sensor
        Controller.Screen.print("Hi.");
        if (inertialSensor.installed()) {
            // inertialSensor.startCalibration();
            Controller.Screen.print("%.2f %2.f %.2f",
                                    inertialSensor.roll(),
                                    inertialSensor.pitch(),
                                    inertialSensor.yaw());
        } else {
            Controller.Screen.print("Inertial sensor not detected. Check port, wire, or sensor.");
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
            leftMotors.setVelocity(-(straightSpeed + turnSpeed), percent);
            rightMotors.setVelocity(-(straightSpeed - turnSpeed), percent);
            leftMotors.spin(forward);
            rightMotors.spin(forward);
        } else {
            leftMotors.stop();
            rightMotors.stop();
        }

        wait(20, msec);
    }
    return 0;
}

void vexcodeInit(void) {
    task rc_auto_loop_task_Controller(tank_drive);
}