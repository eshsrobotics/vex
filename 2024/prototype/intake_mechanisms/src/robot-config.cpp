#include "robot-config.h"

#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Seventeen59A;

// A global instance of controller used for controlling the robot during teleop
controller Controller;

// VEXcode device constructors

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
    // nothing to initialize
}