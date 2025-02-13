/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       FRC1                                                      */
/*    Created:      5/10/2024, 4:03:35 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;

// define your global instances of motors and other devices here

int main() {
    Brain.Screen.printAt(10, 50, "Hello V5");

    while (true) {
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
