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
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::fstream;
using std::stringstream;
using namespace vex;
const string DEFAULT_PREFIX = "LOG";
const string DEFAULT_SUFFIX = "log";

// Keep opening PREFIX0001.txt, PREFIX0002.txt, and so on, until we find one that does not exist, then return the first filename that's free.
//
// This is a workaround for the fact that VEX V5 Brains don't have a timestamp facility worth a hill o' beans.
//
// The padding determines the number of 0s to insert.
string getNextAvailableFilename(const string& prefix = DEFAULT_PREFIX, const string& suffix = DEFAULT_SUFFIX, size_t padding = 5) {
  stringstream stream;

  // What's the first available file number?
  int index = 0;
  const int limit = pow(10, padding) - 1;

  for (; index < limit; ++index) {
    stream.str("");
    stream << prefix;
    stream.width(padding);
    stream.fill('0');
    stream << index;
    stream << "." << suffix;

    fstream file(stream.str(), std::ios::in);
    if (!file) {
      // This index is available!
      return stream.str();
    }
    // Index not available; keep going.
  }

  // Nothing is available.
  return "";
}

int main() {
  // Initializing Robot Controller1figuration. DO NOT REMOVE!
  vexcodeInit();
  /* Brain.SDcard.appendfile(const char *name, uint8_t *buffer, int32_t len);
  Brain.SDcard.exists(const char *name);
  Brain.SDcard.loadfile(const char *name, uint8_t *buffer, int32_t len);
  Brain.SDcard.savefile(const char *name, uint8_t *buffer, int32_t len);
  Brain.SDcard.isInserted();
  Brain.SDcard.size(const char *name); */

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);

  while (true) {
    // Capture the current time as a std::string.

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Next avail. filename: %s", getNextAvailableFilename().c_str());

    {
      fstream file(getNextAvailableFilename().c_str(), std::ios::out);
      file << "This is some file content!\n";
    }

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("%s", getNextAvailableFilename().c_str());
    wait(200, msec);
  }
  // Control never makes it here.
}
