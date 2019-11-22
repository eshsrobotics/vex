// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontRightWheel      motor         1               
// FrontLeftWheel       motor         2               
// BackRightWheel       motor         3               
// BackLeftWheel        motor         4               
// LeftIntake           motor         5               
// RightIntake          motor         6               
// IntakeLift           motor         10              
// TrayPusher           motor         8               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jwilsoniii_23                                    */
/*    Created:      Wed Nov 13 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

void mecanumDrive (int leftRight, int forwardBack, int turn) {
  FrontRightWheel.spin(forward, forwardBack - turn + leftRight, percent);
  BackRightWheel.spin(forward, forwardBack - turn - leftRight, percent);      
  FrontLeftWheel.spin(forward, forwardBack + turn + leftRight, percent);
  BackLeftWheel.spin(forward, forwardBack + turn - leftRight, percent);
}

int main() {
  vexcodeInit();
  // Enough with the slow motors out of the box already!
  IntakeLift.setVelocity(100, percent);
  LeftIntake.setVelocity(90, percent);
  RightIntake.setVelocity(90, percent);
  
  // Initializing Robot Configuration. DO NOT REMOVE!
  
  
  while(true) {
    // allows controller to control both intakes with one button (the left trigger)
    //
    // left intake is automatically configured with robot config    
    
    bool pressedTrigger = false;
    if (Controller1.ButtonL1.pressing()) {
      RightIntake.spin(reverse);
      LeftIntake.spin(fwd);
      pressedTrigger = true;
    } else if (Controller1.ButtonL2.pressing()) {
      RightIntake.spin(fwd);
      LeftIntake.spin(reverse);
      pressedTrigger = true;
    } else {
      RightIntake.stop();
      LeftIntake.stop();
    }
    
    //axis 4 is left joysticks horizontal movement and will be used for strafing 
    int leftRight = Controller1.Axis4.position(percent);

    //axis 3 is the left joysticks vertical movement will be used for forward-backward movement
    int forwardBack = Controller1.Axis3.position(percent);

    //axis 1 is the right joystick horizontal movement and will be used for turning
    int turn = Controller1.Axis1.position(percent);

    // For whatever reason, channels 1 and 3 are flipped in our tests:
    // though our mecanum formula is correct (and copied from last
    // year's bot), the controls for channel 3 are firing when we
    // move channel 1, and vice versa.
    //
    // We can fix this in software, but we are not happy about having to
    // do so.
    std::swap(turn, forwardBack);

    //update drive motor values continously as the driver changes the joystick
    //
    // 2019-11-21: The robot's mecanum wheels were accidentally moved into a
    //             diamond configuration rather than an "X" configuration, so
    //             strafing was reversed.  It's easy to correct in software,
    //             though.
    //
    //   mecanumDrive(leftRight, forwardBack, turn);    
	  mecanumDrive(-leftRight, forwardBack, turn);
  } // end (loop forever)
}
