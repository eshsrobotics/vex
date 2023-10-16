#include "input.h"

using namespace vex;

void tank_drive(double leftSpeedPercent,
                double rightSpeedPercent, 
                motor_group& left, 
                motor_group& right) {

    if (leftSpeedPercent > JOYSTICK_DEADZONE_PERCENT || leftSpeedPercent < -JOYSTICK_DEADZONE_PERCENT) {
        left.spin(directionType::fwd, leftSpeedPercent, percentUnits::pct);
    } else {
        left.stop(ROBOT_BRAKE_TYPE);
    }
}