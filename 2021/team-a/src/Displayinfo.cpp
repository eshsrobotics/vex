#include "vex.h"
 
 using namespace vex; 
  
  void temperatureDisplay() {
    
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    
    // Prints the pitch ( rotation around the side to side axis)
    Brain.Screen.print("Drivetrain temperature: ");
    Brain.Screen.print((Drivetrain.temperature(percent)));
    Brain.Screen.newLine();

    // Prints the acceleration of the y axis.
    Brain.Screen.print("ArmMotorLeft temperature: ");
    Brain.Screen.print((ArmMotorLeft.temperature(percent)));
    Brain.Screen.newLine();

    Brain.Screen.print("ArmMotorRight temperature: ");
    Brain.Screen.print((ArmMotorRight.temperature(percent)));
    Brain.Screen.newLine();

    // Prints the acceleration of the y axis.
    Brain.Screen.print("Y-axis Acceleration (G): ");
    Brain.Screen.print((ArmMotorLeft.temperature(percent)));
    Brain.Screen.newLine();

    // Prints the acceleration of the y axis.
    Brain.Screen.print("Y-axis Acceleration (G): ");
    Brain.Screen.print((ArmMotorLeft.temperature(percent)));
    Brain.Screen.newLine();
    wait(0.2, seconds);
  }