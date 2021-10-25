// ---- START VEXCODE Controller1FIGURED DEVICES ----
// Robot Controller1figuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE Controller1FIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\brandon                                          */
/*    Created:      Sun Aug 11 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Robot Controller1figuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1
// Motor2               motor         2
// Motor3               motor         3
// Motor4               motor         4
// Motor5               motor         5
// Motor6               motor         6
// Motor7               motor         7
// Motor8               motor         8
// Motor9               motor         9
// Motor10              motor         10
// Motor11              motor         11
// Motor12              motor         12
// Motor13              motor         13
// Motor14              motor         14
// Motor15              motor         15
// Motor16              motor         16
// Motor17              motor         17
// Motor18              motor         18
// Motor19              motor         19
// Motor20              motor         20
// Controller1troller1          Controller1troller
// ---- END VEXCODE Controller1FIGURED DEVICES ----

// To complete the VEXcode Pro V5 project upgrade process, please follow the
// steps below.
//
// 1. You can use the Robot Controller1figuration window to recreate your V5
// devices
//   - including any motors, sensors, 3-wire devices, and Controller1trollers.
//
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Controller1figuration window.
//
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

#include "SD_Card_Data.h"
#include "vex.h"


using namespace vex;


int main() {
  // Initializing Robot Controller1figuration. DO NOT REMOVE!
  vexcodeInit();

  if (Brain.SDcard.isInserted()) {
    // create a file with long filename
    ofs.open("Run.csv", std::ofstream::out);
    sensorHeader();
    while (true) {

      sensorWriter();

      vex::task::sleep(10);

      drive();

      if (/*Controller1.ButtonB.pressing() == 1 &&
          Controller1.ButtonX.pressing() == 1 &&
          Controller1.ButtonUp.pressing() == 1 &&
          Controller1.ButtonDown.pressing() == 1 &&*/
          Controller1.ButtonL1.pressing() == 1 &&
          Controller1.ButtonL2.pressing() == 1 &&
          Controller1.ButtonR2.pressing() == 1 &&
          Controller1.ButtonR1.pressing() == 1) {
        break;
      }
    }

    ofs.close();
    Brain.Screen.printAt(10, 40, "done");
    stopMotor();
  } else {
    Brain.Screen.printAt(10, 40, "No SD Card");
  }
}

