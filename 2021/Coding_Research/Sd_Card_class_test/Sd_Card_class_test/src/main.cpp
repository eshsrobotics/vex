// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// m                    motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor4               motor         4               
// Controller1          controller                    
// Drivetrain           drivetrain    10, 11, 12, 13, 5
// Optical6             optical       6               
// Rotation7            rotation      7               
// Distance8            distance      8               
// GPS9                 gps           9               
// LineTrackerA         line          A               
// LightB               light         B               
// PotentiometerV2C     potV2         C               
// DigitalOutD          digital_out   D               
// Vision14             vision        14              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor4               motor         4               
// Controller1          controller                    
// Drivetrain           drivetrain    10, 11, 12, 13, 5
// Optical6             optical       6               
// Rotation7            rotation      7               
// Distance8            distance      8               
// GPS9                 gps           9               
// LineTrackerA         line          A               
// LightB               light         B               
// PotentiometerV2C     potV2         C               
// DigitalOutD          digital_out   D               
// Vision14             vision        14              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor4               motor         4               
// Controller1          controller                    
// Drivetrain           drivetrain    10, 11, 12, 13, 5
// Optical6             optical       6               
// Rotation7            rotation      7               
// Distance8            distance      8               
// GPS9                 gps           9               
// LineTrackerA         line          A               
// LightB               light         B               
// PotentiometerV2C     potV2         C               
// DigitalOutD          digital_out   D               
// Vision14             vision        14              
// ---- END VEXCODE CONFIGURED DEVICES ----

/*
Using the SD card reader
  1. See if there is a SD card in the reader --done--
  2. Make a .csv file
  3. Check to see if a file has the same name before making the file  --done--
  4. Change the file name --done--
  5. Save sensor data to SD card
*/

#include "vex.h"
#include <fstream>
#include <sstream>
#include <string>

using std::fstream;
using std::string;
using std::stringstream;
using namespace vex;
const string DEFAULT_PREFIX = "LOG";
const string DEFAULT_SUFFIX = "log";

// Keep opening PREFIX0001.txt, PREFIX0002.txt, and so on, until we find one
// that does not exist, then return the first filename that's free.
//
// This is a workaround for the fact that VEX V5 Brains don't have a timestamp
// facility worth a hill o' beans.
//
// The padding determines the number of 0s to insert.
string getNextAvailableFilename(const string &prefix = DEFAULT_PREFIX,
                                const string &suffix = DEFAULT_SUFFIX,
                                size_t padding = 5) {
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

  clearAllScreens();
  Brain.Screen.setCursor(1, 1);
  if (Brain.SDcard.isInserted()) {

    while (true) {

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Next avail. filename: %s",
                         getNextAvailableFilename().c_str());

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
  } else {
    Brain.Screen.printAt(1, 1, " No SD card");
  }


}

