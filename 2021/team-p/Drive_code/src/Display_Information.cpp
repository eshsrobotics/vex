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
  Brain.Screen.setPenColor(black);
  Brain.Screen.newLine();

  // Prints the ArmLeft temperature.
  Brain.Screen.print("ArmLeft temperature: ");
  temperatureColour(ArmLeft.temperature(percent));
  Brain.Screen.print((ArmLeft.temperature(percent)));
  Brain.Screen.setPenColor(black);
  Brain.Screen.newLine();

  // Prints the ArmRight temperature.
  Brain.Screen.print("ArmRight temperature: ");
  temperatureColour(ArmRight.temperature(percent));
  Brain.Screen.print((ArmRight.temperature(percent)));
  Brain.Screen.setPenColor(black);
  Brain.Screen.newLine();

  wait(0.2, seconds);
}

