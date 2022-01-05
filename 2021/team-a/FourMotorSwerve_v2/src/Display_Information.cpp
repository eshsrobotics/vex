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

  // Prints the pMotor temperature.
  Brain.Screen.print("pMotor temperature(percent): ");
  temperatureColour(pMotor.temperature(percent));
  Brain.Screen.print((pMotor.temperature(percent)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();
}

void drivetrainTemperatureDisplay() {
  // Prints the Drivetrain temperature

  /* the display on the brain should look like this:


                     Drivetrain temperature
           FrontLeftMotor 000°F FrontRightMotor 000°F
           RearLeftMotor  000°F RearRightMotor  000°F


  */
  Brain.Screen.setPenColor(white);
  Brain.Screen.print("            Drivetrain temperature ");
  Brain.Screen.newLine();

  Brain.Screen.print("FrontLeftMotor: ");
  temperatureColour(FrontLeftMotor.temperature(celsius));
  Brain.Screen.print(FrontLeftMotor.temperature(celsius));
  Brain.Screen.setPenColor(white);

  Brain.Screen.print("  FrontRightMotor: ");
  temperatureColour(FrontRightMotor.temperature(celsius));
  Brain.Screen.print(FrontRightMotor.temperature(celsius));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  Brain.Screen.print("RearLeftMotor:  ");
  temperatureColour(RearLeftMotor.temperature(celsius));
  Brain.Screen.print(RearLeftMotor.temperature(celsius));
  Brain.Screen.setPenColor(white);
  Brain.Screen.print("  RearRightMotor:  ");
  temperatureColour(RearRightMotor.temperature(celsius));
  Brain.Screen.print(RearRightMotor.temperature(celsius));

  Brain.Screen.newLine();

  Brain.Screen.setPenColor(white);

  temperatureDisplay();
  Brain.Screen.newLine();

  /* the display on the Contoller should look like this:


               Drivetrain tempe
              FLM 000°F FRM 000°F
              RLM 000°F RRM 000°F


  */

  Controller1.Screen.print("   Drivetrain temp: ");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.temperature(celsius));

  Controller1.Screen.print(" FRM: ");
  Controller1.Screen.print(FrontRightMotor.temperature(celsius));
  Controller1.Screen.newLine();

  Controller1.Screen.print("RLM: ");
  Controller1.Screen.print(RearLeftMotor.temperature(celsius));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.temperature(celsius));

  //wait(500, msec);
}
