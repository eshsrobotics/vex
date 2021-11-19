#include "vex.h"

using namespace vex;

void clearAllScreens() {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
}

void temperatureColour(double temperatureReading) {
  if (temperatureReading >= 90) {
    Brain.Screen.setPenColor(red);
  } else if (temperatureReading < 90 && temperatureReading >= 80) {
    Brain.Screen.setPenColor(yellow);
  } else {
    Brain.Screen.setPenColor(green);
  }
}

void temperatureDisplay() {

  Brain.Screen.setCursor(1, 1);

  // Prints the Drivetrain temperature
  Brain.Screen.print("Drivetrain temperature: ");
  temperatureColour(Drivetrain.temperature(percent));
  Brain.Screen.print((Drivetrain.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  // Prints the unused_right_now temperature.
  Brain.Screen.print("unused_right_now temperature: ");
  temperatureColour(unused_right_now.temperature(percent));
  Brain.Screen.print((unused_right_now.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  // Prints the Arm temperature.
  Brain.Screen.print("Arm temperature: ");
  temperatureColour(Arm.temperature(percent));
  Brain.Screen.print((Arm.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  wait(0.2, seconds);
}

