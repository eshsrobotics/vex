// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightFront           motor         1               
// LeftFront            motor         19              
// RightBack            motor         3               
// LeftBack             motor         4               
// Controller1          controller                    
// LeftLineTracker      line          A               
// MiddleLineTracker    line          B               
// RightLineTracker     line          C               
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

// This is a loop function for the drive motors.
//
// strafeLeftRight: the percentage (-100 to 100) of speed of which the robot
// will go- either strafing to the left or right forwardBack: the percentage
// (-100 to 100) of speed of which the robot will go- either forward or back
// turnLeftRight:the percentage (-100 to 100) of speed of which the robot will
// go-  either turning left or right.

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

// How far from the center the joystick must move to have an effect.
const int deadzone_threshold = 10;

// Checks if the deadzone applies to the joystick input.
int threshold(int joystickValue) {
  if (joystickValue >= -deadzone_threshold && joystickValue <= deadzone_threshold) {
    return 0;
  }
  return joystickValue;
} 

// States that are used during fake autonomous.
enum State {
  START = 1,
  LEFT_FORWARD,
  RIGHT_FORWARD,
  RIGHT_BACKWARD,
  LEFT_BACKWARD,
  END
};

// Current state of fake autonomous state machine.
State state = START;

// Speed and length of drive during autonomous diamond.
int drive_time_ms = 500;
int drive_speed_percentage = 55;

// Instantaneous function that drives robot in diamond pattern.
// Fake autonomus mode to be replaced at a later date.
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

// Prints sensor values on controller display and brain display.
//
// This function is used for debugging.
void printSensorValues() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Left sensor: %.1f", LeftLineTracker.value(percent));
  Controller1.Screen.print("Middle sensor: %.1f", MiddleLineTracker.value(percent));
  Controller1.Screen.print("Right sensor: %.1f", RightLineTracker.value(percent));
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.clearScreen();
  Brain.Screen.print("Left sensor: %.1f", LeftLineTracker.value(percent));
  Brain.Screen.print("Middle sensor: %.1f", MiddleLineTracker.value(percent));
  Brain.Screen.print("Right sensor: %.1f", RightLineTracker.value(percent));
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

      // Adjust the joystick for the deadzone.
      mechDrive(threshold(leftright), threshold(forwardbackward), threshold(turnclockwise));
    }
    
    // Executes autonomous if runnable.
    diamond_drive(button_press_time_ms);
  
    // Print the line sensors trackers.
    printSensorValues();
  }
}
