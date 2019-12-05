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

bool sneak = false;

void mecanumDrive(int leftRight, int forwardBack, int turn) {
  // If sneak is enabled, reduce speed.
  double multiplier = 1.0;
  if (sneak) {
    multiplier = SNEAK_PERCENTAGE;
  }

  FrontRightWheel.spin(forward, multiplier * (forwardBack - turn + leftRight), percent);
  BackRightWheel.spin(forward,  multiplier * (forwardBack - turn - leftRight), percent);
  FrontLeftWheel.spin(forward,  multiplier * (forwardBack + turn + leftRight), percent);
  BackLeftWheel.spin(forward,   multiplier * (forwardBack + turn - leftRight), percent);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Unlike our other motors, the IntakeLift needs to maintain its position by
  // expending electrical power.  So we're not just going to set a speed and cut
  // off power when controls are released; instead, we adjust *this* variable,
  // and set position to it.
  double position = IntakeLift.position(turns);
  const double BOTTOM_POSITION = position;
  const double TOP_POSITION = position + 75;
  double positionIncrement = 0.05;
  const double positionIncrementIncrement = 0.05; // 0.01;

  // Enough with the slow motors out of the box already!
  IntakeLift.setVelocity(100, percent);
  LeftIntake.setVelocity(90, percent);
  RightIntake.setVelocity(90, percent);

  while (true) {
    // allows controller to control both intakes with one button (the left
    // trigger)
    //
    // left intake is automatically configured with robot config
    if (Controller1.ButtonL2.pressing()) {
      RightIntake.spin(reverse);
      LeftIntake.spin(fwd);
    } else if (Controller1.ButtonL1.pressing()) {
      RightIntake.spin(fwd);
      LeftIntake.spin(reverse);
    } else {
      RightIntake.stop();
      LeftIntake.stop();
    }

    // Sneak control
    if (Controller1.ButtonA.pressing()) {
      sneak = true;
    } else {
      sneak = false;
    }

    // axis 4 is left joysticks horizontal movement and will be used for
    // strafing
    int leftRight = Controller1.Axis4.position(percent);

    // axis 3 is the left joysticks vertical movement will be used for
    // forward-backward movement
    int forwardBack = Controller1.Axis3.position(percent);

    // axis 1 is the right joystick horizontal movement and will be used for
    // turning
    int turn = Controller1.Axis1.position(percent);

    // For whatever reason, channels 1 and 3 are flipped in our tests:
    // though our mecanum formula is correct (and copied from last
    // year's bot), the controls for channel 3 are firing when we
    // move channel 1, and vice versa.
    //
    // We can fix this in software, but we are not happy about having to
    // do so.
    std::swap(turn, forwardBack);

    // update drive motor values continously as the driver changes the joystick
    mecanumDrive(leftRight, forwardBack, turn);

    // Sets the position of the intake lift using increments of 5 degrees
    //
    // We know the proper way to move the motor via encoders: IntakeLift.spinToPosition().
    //
    // But it is not easy to detemrine when that function should be called.
    if (Controller1.ButtonR2.pressing()) {
      IntakeLift.spin(forward);
      // We're assuming that this will be downward movement
      // position -= positionIncrement;      
      // positionIncrement += positionIncrementIncrement;
      // if (position < BOTTOM_POSITION) {
      //   position = BOTTOM_POSITION;
      // } else {
        
      // }      
    } else if (Controller1.ButtonR1.pressing()) {
      IntakeLift.spin(reverse);
      // This is presumed to be upward movement.
      // position += positionIncrement;      
      // positionIncrement += positionIncrementIncrement;
      // if (position > TOP_POSITION) {
      //   position = TOP_POSITION;
      // } else {
        
      // }      
    } else {
      bool waitForCompletion = false;
      IntakeLift.spinToPosition(IntakeLift.position(degrees), degrees, waitForCompletion);
      // Decelerate.
      // positionIncrement -= positionIncrementIncrement;
      // if (positionIncrement < 0) {
      //   positionIncrement = 0;
      // }
    }    
    
  } // end (loop forever)
}
