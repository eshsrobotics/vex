/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jchartier_23                                     */
/*    Created:      Wed Dec 04 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void printPositions(motor& m, double goal) {
    // Getting the position of the IntakeLift and displaying in the controller    
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Real: %.2f", m.position(turns));
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Goal: %.2f", goal);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Motor1.setVelocity(100, percent);

  
  double initialPosition = Motor1.position(turns); // Position is in turns.
  double goalPosition = initialPosition;

  // You can liken these two variables to the dial of an accelerometer.
  //
  // The goalPosition is where the dial needs to end up.
  // The goalPositionIncrement is how fast the dial is currently turning.
  // The goalPositionIncrementIncrement is how fast the dial can speed up or slow down.
  //
  // Left to its own devices (that is, when the user releases the button), the dial
  // slows down to a stop on its own -- it decelerates.
  //
  // Pressing either the forward or back buttons accelerates the dial, but only by
  // a constant amount.
  double goalPositionIncrement = 0.05;
  const double goalPositionIncrementIncrement = 0.01;

  while(true) {
          
    if (Controller1.ButtonL1.pressing()) {

      goalPosition += goalPositionIncrement;
      goalPositionIncrement += goalPositionIncrementIncrement;

    } else if (Controller1.ButtonL2.pressing()) {      
      goalPosition -= goalPositionIncrement;
      goalPositionIncrement += goalPositionIncrementIncrement;

    } else {

      goalPositionIncrement -= goalPositionIncrementIncrement;
      if (goalPositionIncrement < 0) {
        goalPositionIncrement = 0;
      }
      Motor1.stop();
      printPositions(Motor1, goalPosition);
    }    
    Motor1.setPosition(goalPosition, turns);
    wait(20, msec);
  } 
}
