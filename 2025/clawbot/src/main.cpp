/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       eoson                                                     */
/*    Created:      10/12/2025, 4:25:36 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
brain       Brain;

const int LCLAW_PORT = 1;
const int RCLAW_PORT = 2;
const int MaximumClawSpeedPercent = 50;

motor LMotor = motor(LCLAW_PORT, true);
motor RMotor = motor(RCLAW_PORT);
motor_group ClawMotors = motor_group (LMotor, RMotor);
bumper Button = bumper(Brain.ThreeWirePort.A);
limit OpeningLimitSwitch = limit(Brain.ThreeWirePort.B);
limit ClosingLimitSwitch = limit(Brain.ThreeWirePort.C);

int main() {

    //Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while (true) {
        
        if (Button.pressing()) {
            // Close the claw
            if (ClosingLimitSwitch.pressing()) {
                ClawMotors.stop(hold);
            } else {
                ClawMotors.spin(forward, MaximumClawSpeedPercent, percentUnits::pct);
            }
        } else {
            // Open the claw
            if (OpeningLimitSwitch.pressing()) {
                ClawMotors.stop(hold);
            } else {
                ClawMotors.spin(reverse, MaximumClawSpeedPercent, percentUnits::pct);
            }
        }
        
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
