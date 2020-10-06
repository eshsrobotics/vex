// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightFront           motor         1
// LeftFront            motor         19
// RightBack            motor         3
// LeftBack             motor         4
// Controller1          controller
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Wilson Family                                    */
/*    Created:      Mon Sep 14 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// This is a loop fuction for the drive motors
//
// strafeLeftRight: the percentage (-100 to 100) of speed of which the robot
// will go- either strafing to the left or right forwardBack: the percentage
// (-100 to 100) of speed of which the robot will go- either forward or back
// turnLeftRight:the percentage (-100 to 100) of speed of which the robot will
// go-  either turning left or right

void mechDrive(int strafeLeftRight, int forwardBack, int turnLeftRight) {

  RightFront.spin(forward, forwardBack - strafeLeftRight - turnLeftRight,
                  percent);
  RightBack.spin(forward, forwardBack + strafeLeftRight - turnLeftRight,
                 percent);
  LeftFront.spin(forward, forwardBack + strafeLeftRight + turnLeftRight,
                 percent);
  LeftBack.spin(forward, forwardBack - strafeLeftRight + turnLeftRight,
                percent);
}
enum State {
  START = 1,
  LEFT_FORWARD,
  RIGHT_FORWARD,
  RIGHT_BACKWARD,
  LEFT_BACKWARD,
  END
};
State state = START;
int drive_time_ms = 1500;
int drive_speed_percentage = 55;

void diamond_drive(double button_press_time_ms) {
  double elapsed_time_ms = Brain.timer(msec) - button_press_time_ms;
  if (state == START) {
    state = LEFT_FORWARD;

  } else if (state == LEFT_FORWARD) {
    mechDrive(drive_speed_percentage, drive_speed_percentage, 0);
    if (elapsed_time_ms >= drive_time_ms) {
      state = RIGHT_FORWARD;
    }
  } else if (state == RIGHT_FORWARD) {
    mechDrive(-drive_speed_percentage, drive_speed_percentage, 0);
    if (elapsed_time_ms >= 2 * drive_time_ms) {
      state = RIGHT_BACKWARD;
    }
  } else if (state == RIGHT_BACKWARD) {
    mechDrive(-drive_speed_percentage, -drive_speed_percentage, 0);
    if (elapsed_time_ms >= 3 * drive_time_ms) {
      state = LEFT_BACKWARD;
    }
  } else if (state == LEFT_BACKWARD) {
    mechDrive(drive_speed_percentage, -drive_speed_percentage, 0);
    if (elapsed_time_ms >= 4 * drive_time_ms) {
      state = END;
    }
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double button_press_time_ms = 0;

  while (true) {
    int leftright = Controller1.Axis4.position(percent);
    int forwardbackward = Controller1.Axis3.position(percent);
    int turnclockwise = Controller1.Axis1.position(percent);

    
    if (Controller1.ButtonLeft.pressing() && (state == START || state == END)) {
      // Initialize autonomous.
      state = LEFT_FORWARD;

      button_press_time_ms = Brain.timer(msec);

    } else if (!Controller1.ButtonLeft.pressing()) {
      // Terminate autonomous.
      state = END;
      mechDrive(leftright, forwardbackward, turnclockwise);
    }
    // Executes autonomous if runnable.
    diamond_drive(button_press_time_ms);
  }
}
