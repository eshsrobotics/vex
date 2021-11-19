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

  // Prints the ArmMotorLeft temperature.
  Brain.Screen.print("ArmMotorLeft temperature: ");
  temperatureColour(ArmMotorLeft.temperature(percent));
  Brain.Screen.print((ArmMotorLeft.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  // Prints the ArmMotorRight temperature.
  Brain.Screen.print("ArmMotorRight temperature: ");
  temperatureColour(ArmMotorRight.temperature(percent));
  Brain.Screen.print((ArmMotorRight.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  // Prints the LeftLiftMotor temperature.
  Brain.Screen.print("LiftMotor temperature(percent): ");
  temperatureColour(LeftLiftMotor.temperature(percent));
  Brain.Screen.print((LeftLiftMotor.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();
  
  // Prints the RightLiftMotor temperature.
  Brain.Screen.print("LiftMotor temperature(percent): ");
  temperatureColour(RightLiftMotor.temperature(percent));
  Brain.Screen.print((RightLiftMotor.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  
}
 
 void Motor_RPM(){
   
 }