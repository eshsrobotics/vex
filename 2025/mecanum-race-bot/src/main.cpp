/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       FRC1                                                      */
/*    Created:      4/25/2024, 4:57:54 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// We really oughtta start not making that port numbering mistake (the port numbers were all one too high thanks to Vex design)...
const int FRONT_LEFT_PORT = 5 - 1;
const int FRONT_RIGHT_PORT = 10 - 1;
const int BACK_LEFT_PORT = 3 - 1;
const int BACK_RIGHT_PORT = 6 - 1;


//When the robot is oriented so the brain is on the left side, the robot is facing forward

vex::controller Controller;
vex::motor front_left(FRONT_LEFT_PORT);
vex::motor front_right(FRONT_RIGHT_PORT, true);
vex::motor back_left(BACK_LEFT_PORT);
vex::motor back_right(BACK_RIGHT_PORT, true);

void mecanum_drive(int front_back_percent, int left_right_percent, int turn_percent) {
    front_left.spin(directionType::fwd, front_back_percent + turn_percent + left_right_percent, percentUnits::pct);
    front_right.spin(directionType::fwd, front_back_percent - turn_percent - left_right_percent, percentUnits::pct);
    back_left.spin(directionType::fwd, front_back_percent + turn_percent - left_right_percent, percentUnits::pct);
    back_right.spin(directionType::fwd, front_back_percent - turn_percent + left_right_percent, percentUnits::pct);
}

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

int main() {

    while (true) {
        int forward_back_speed = Controller.Axis3.position();
        int left_right_speed = Controller.Axis1.position();
        int turn_speed = Controller.Axis4.position();
        mecanum_drive(forward_back_speed, left_right_speed, turn_speed);

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
