/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       FRC1                                                      */
/*    Created:      10/10/2024, 4:22:01 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;

// define your global instances of motors and other devices here
bumper motor_turn_button = bumper(Brain.ThreeWirePort.A);

motor ucheMotor = motor(PORT11, true);

controller Controller = controller();

int main() {
    Brain.Screen.printAt(10, 50, "Hello V5");

    while (true) {
        if (Controller.Axis3.position() > 0) {
            ucheMotor.spin(directionType::fwd, 100, percentUnits::pct);
        } else if (Controller.Axis3.position() < 0) {
            ucheMotor.spin(directionType::fwd, -100, percentUnits::pct);
        }

        if (motor_turn_button.pressing()) {
            ucheMotor.spin(directionType::fwd, 120, percentUnits::pct);
        }

        if (Controller.Axis3.position() == 0
            && motor_turn_button.pressing() == false) {
            ucheMotor.stop();
        }

        Brain.Screen.printAt(
            20,
            60,
            "Uche was here: %f ",
            ucheMotor.velocity(percentUnits::pct)
        );

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
