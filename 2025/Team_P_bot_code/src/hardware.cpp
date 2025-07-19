#include "hardware.h"
#include "vex.h"
#include <algorithm>
#include <memory>

using std::max;
using std::min;
using std::unique_ptr;

std::vector<vex::motor> driveMotors;

void createDriveMotors(std::vector<int> driveMotorPorts) {

    size_t numberOfMotorPorts = driveMotorPorts.size();

    for (size_t i = 0; i < numberOfMotorPorts; i++) {

        // If we encounter a negative port number, then that means we need to
        // reverse the corresponding motor when constructing it.
        vex::motor motor = vex::motor(abs(driveMotorPorts[i]),
                                      driveMotorPorts[i] > 0 ? false : true);

        driveMotors.emplace_back(motor);
    } 

}

void drive(double frontBackSpeed, double turnSpeed) {

    size_t numberOfMotors = driveMotors.size();

    double leftMotorSpeed = (frontBackSpeed + turnSpeed);
    double rightMotorSpeed = (frontBackSpeed - turnSpeed);
    leftMotorSpeed = max(-100.0, min(leftMotorSpeed, 100.0));
    rightMotorSpeed = max(-100.0, min(rightMotorSpeed, 100.0));

    for (size_t i = 0; i < numberOfMotors/2; i++) {

        if(fabs(leftMotorSpeed) > DEADZONE) {
            driveMotors[i].spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
        } else {
            driveMotors[i].stop(vex::brakeType::brake);
        }
        
    }

    for (size_t i = numberOfMotors/2; i < numberOfMotors; i++) {
        
        if(fabs(rightMotorSpeed) > DEADZONE) {
            driveMotors[i].spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);
        } else {
            driveMotors[i].stop(vex::brakeType::brake);
        }

    }



}

void testMotors(int timeInMillis) {

    while (true) {

        for (size_t i = 0; i < driveMotors.size(); i++) {

            driveMotors[i].spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
            wait(timeInMillis, vex::msec);
            driveMotors[i].stop(vex::brakeType::brake);

        }

    }

}

