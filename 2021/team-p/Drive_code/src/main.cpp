/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\BoofTop 1                                        */
/*    Created:      Wed Oct 06 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    19, 12          
// ArmLeft              motor         20              
// ArmRight             motor         13              
// LeftArmBumper        bumper        G               
// RightArmBumper       bumper        H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
int speed = 50;
int speedSlow = speed/2;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Controls the right shoulder buttons on the controllers to make the arms move up and down at 50% speed
  while(true){
    if(Controller1.ButtonR1.pressing()){
      ArmLeft.spin(forward, speed, pct);
      ArmRight.spin(forward, speed, pct);
    }
    else if(Controller1.ButtonR2.pressing()){
      if(!LeftArmBumper.pressing())
      ArmLeft.spin(reverse, speed, pct);
      if(!RightArmBumper.pressing())
      ArmRight.spin(reverse, speed, pct);
    }
    else {
    ArmLeft.stop(hold);
    ArmRight.stop(hold);
    }
    
   //Controls the left shoulder buttons to make the arms go a slower speed (25%)
    if(Controller1.ButtonL1.pressing()){
      ArmLeft.spin(forward, speedSlow, pct);
      ArmRight.spin(forward, speedSlow, pct);
    }
    else if(Controller1.ButtonL2.pressing()){
      if(!LeftArmBumper.pressing())
      ArmLeft.spin(reverse, speedSlow, pct);
      if(!RightArmBumper.pressing())
      ArmRight.spin(reverse, speedSlow, pct);
    }
    else {
    ArmLeft.stop(hold);
    ArmRight.stop(hold);
    }
  }
}
