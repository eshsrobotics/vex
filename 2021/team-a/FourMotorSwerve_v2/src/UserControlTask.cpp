#include "vex.h"

using namespace vex;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// This is the main execution loop for the user control program.
// Each time through the loop your program should update motor + servo
// values based on feedback from the joysticks.

// The state of the claws pneumatic starts false this is changed by the function
// pvoid PneumaticControlClaw();
bool PneumaticStateClaw = false;

// The state of the spatulas pneumatic starts false this is changed by the
// function pvoid PneumaticControlClaw();
bool PneumaticStateSpatula = false;

void usercontrol(void) {

  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();

  Brain.Screen.setCursor(1, 1);
  Controller1.Screen.setCursor(1, 1);

  // Only attach callback functions onece outside the while loop

  // Activate the pnuematics by looking at the Pneumnatic control function
  // If controller1.buttonB is realeased the state on the claws pnumatic state
  // changes from true to false or false to true If controller1.buttonY is
  // realeased the state on the spatula pnumatic state changes from true to
  // false or false to true
  Controller1.ButtonB.released(PneumaticControlClaw);
  Controller1.ButtonY.released(PneumaticControlSpatula);

  // User control code here, inside the loop
  while (1) {

    Brain.Screen.clearScreen();
    Controller1.Screen.clearScreen();

    Brain.Screen.setCursor(1, 1);
    Controller1.Screen.setCursor(1, 1);

    // Moves mobile goal 90 degree arm forward or backward

    if (Controller1.ButtonR1.pressing()) {

      LeftLiftMotor.spin(forward, 100, percent);
      RightLiftMotor.spin(forward, 100, percent);
    } else if (Controller1.ButtonR2.pressing()) {

      LeftLiftMotor.spin(reverse, 35, percent);
      RightLiftMotor.spin(reverse, 35, percent);

    } else {

      LeftLiftMotor.stop(hold);
      RightLiftMotor.stop(hold);
    }

    // Moves four bar arm up and down to place mobile goals on platforms

    if (Controller1.ButtonL1.pressing()) {

      ArmMotorLeft.spin(forward, 100, percent);
      ArmMotorRight.spin(forward, 100, percent);

    } else if (Controller1.ButtonL2.pressing()) {

      ArmMotorLeft.spin(reverse, 80, percent);
      ArmMotorRight.spin(reverse, 80, percent);

    } else {

      ArmMotorLeft.stop(hold);
      ArmMotorRight.stop(hold);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
    // prevent wasted resources.

    drivetrainTemperatureDisplay();
  }
}

// Functions, place all functions here

// Changes the pneumatic state of claw from true to false

void PneumaticControlClaw() {

  if (PneumaticStateClaw == true)
    PneumaticStateClaw = false;
  else
    PneumaticStateClaw = true;

  PneumaticClaw.set(PneumaticStateClaw);
}

// Changes the pneumatic state of spatula from ture to false

void PneumaticControlSpatula() {

  if (PneumaticStateSpatula == true)
    PneumaticStateSpatula = false;
  else
    PneumaticStateSpatula = true;

  PneumaticSpatula.set(PneumaticStateSpatula);
}