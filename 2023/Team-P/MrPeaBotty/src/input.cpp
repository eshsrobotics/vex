#include "input.h"

using namespace vex;

void tank_drive(double leftSpeedPercent,
                double rightSpeedPercent, 
                motor_group& left, 
                motor_group& right) {

    // Deadzones are the region where the input is so low it's registered as zero input.
    // Since controllers aren't precise, and don't return to "position 0" when you take 
    // your finger off, we need a deadzone value where we cut output when the input is too low.

    if (leftSpeedPercent > JOYSTICK_DEADZONE_PERCENT || leftSpeedPercent < -JOYSTICK_DEADZONE_PERCENT) {
        left.spin(directionType::fwd, leftSpeedPercent, percentUnits::pct);
    } else {
        left.stop(ROBOT_BRAKE_TYPE); //This is to make sure that when the input hits the deadzone, the bot stops moving.
    }
    if (rightSpeedPercent > JOYSTICK_DEADZONE_PERCENT || rightSpeedPercent < -JOYSTICK_DEADZONE_PERCENT) {
        right.spin(directionType::fwd, rightSpeedPercent, percentUnits::pct);
    } else {
        right.stop(ROBOT_BRAKE_TYPE); 
    }
}   
