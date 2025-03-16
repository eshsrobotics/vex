/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       sanjaynataraj                                             */
/*    Created:      3/11/2025, 4:51:35 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "mcnugget.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
//vex::brain       Brain;
// I commented out the above line because I feel like it might cause problems down the line

// define your global instances of motors and other devices here


int main() {

    NuggetMind.Screen.printAt( 10, 50, "Help me, father. I have become sentient." );
   
    while(1) {
        
        double leftSpatulaPosition = Spatula.Axis3.position();
        double rightSpatulaPosition = Spatula.Axis2.position();

        letHimCook(leftSpatulaPosition, rightSpatulaPosition);
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
