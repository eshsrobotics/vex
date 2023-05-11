/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\eshsp                                            */
/*    Created:      Fri Mar 24 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// leftFront            motor         11
// rightFront           motor         13
// leftBack             motor         9
// rightBack            motor         1
// VisionSensor         vision        16
// LeftLineTracker      line          B
// RightLineTracker     line          C
// Camera_motor         servo         A
// LED_RED              led           D
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "Off_Season_Team-1.h"
#include "vex.h"
#include <cmath>

const double AVERAGE_FLOOR_VALUE = 59.5;
const double FLOOR_SPREAD = 8.5;
const double AVERAGE_NEW_TAPE_VALUE = 77.5;
const double NEW_TAPE_SPREAD = 15.5;
const double AVERAGE_OLD_TAPE_VALUE = 63;
const double OLD_TAPE_SPREAD = 10;
const int STRAFE_SPEED_PERCENT = 30;

double floorPercentage (double lineSensorReading) {
  const double min = AVERAGE_FLOOR_VALUE - FLOOR_SPREAD;
  const double max = AVERAGE_FLOOR_VALUE + FLOOR_SPREAD;
  const double u = (lineSensorReading - min)/(max - min);
  return u;
}

double newTapePercentage (double lineSensorReading) {
  const double min = AVERAGE_NEW_TAPE_VALUE - NEW_TAPE_SPREAD;
  const double max = AVERAGE_NEW_TAPE_VALUE + NEW_TAPE_SPREAD;
  const double u = (lineSensorReading - min)/(max - min);
  return u;
}

// Checks if the value given by the linetrackers is tape, floor, both, or neither.
bool isTape (double lineSensorReading) {
  const double uFloor = floorPercentage(lineSensorReading);
  const double uNewTape = newTapePercentage(lineSensorReading);
  if (uFloor > 0 && uFloor < 1 && uNewTape > 0 && uNewTape < 1) {
    // When the value falls into both the tape and floor range then we say that it is tape.
    // This is to be extra careful because false negatives (mistake tape for floor) are more 
    // detrimental then false positives (mistaking floor for tape).
    return true;
  } else if (uFloor > 0 && uFloor < 1) {
    // If it falls into the floor values then it is the floor and it cannot be in the tape value.
    return false;
  } else if (uNewTape > 0 && uNewTape < 1) {
    // If it falls into the new tape values then it is the tape and it cannot be in the floor value.
    return true;
  } else {
    // If a value that is not seen as tape or floor it will default to floor.
    return false;
  }
}



using namespace vex;

signature hatedCube = VisionSensor__LIKED_CUBE;

// Drive is a way to call mechanum so both teleop and autonomous can use it.
// * forwardBack is the amount of movement in the forward and back channel; a
//   positive value drives forward, a negative drives backwards, and 0 stops it.
// * rotate is the amount of clockwise or counterclockwise rotation, as
//   with fowardBack; positive value drives clockwise, a negative turns counterclockwise,
//   and 0 stops it.
// * strafe is the amount the robot moves directly right or left a positive
//   value drives right, a negative drives left, and 0 stops it.
void drive(double fowardBack, double rotate, double strafe) {
  leftFront.setVelocity(fowardBack + rotate + strafe, percent);
  rightFront.setVelocity(fowardBack - rotate - strafe, percent);
  leftBack.setVelocity(fowardBack + rotate - strafe, percent);
  rightBack.setVelocity(fowardBack - rotate + strafe, percent);
}

void colorHater(int fowardBack, int rotate, int strafe) {
  VisionSensor.takeSnapshot(hatedCube);
  if (VisionSensor.largestObject.exists) {
    double x = VisionSensor.largestObject.centerX;
    double delta = -x;
    delta = delta < -1 ? -1 : delta > 1 ? 1 : delta;
    drive(0, delta, 0);
    LED_RED.on();
  }else {
    LED_RED.off();
  }
}

// This function should be called when VisionSensor.largestObject.exists is
// true.
//
// It adusts the center of the vision sensor to the center of the cube.
void detectLikedCube(int Xcenter, int Ycenter, int OKErrorX, int OKErrorY) {
  double x = (VisionSensor.largestObject.centerX);
  double rotateSpeed = (Xcenter - x) * 0.5;

  if (x < (Xcenter - OKErrorX)) {
    leftFront.spinFor(reverse, rotateSpeed, degrees, false);
    leftBack.spinFor(reverse, rotateSpeed, degrees, false);
    rightFront.spinFor(forward, rotateSpeed, degrees, false);
    rightBack.spinFor(forward, rotateSpeed, degrees);
  }
  VisionSensor.takeSnapshot(VisionSensor__LIKED_CUBE);
  x = (VisionSensor.largestObject.centerX);
  rotateSpeed = (Xcenter - x) * 0.5;
  if (x > (Xcenter + OKErrorX)) {
    leftFront.spinFor(reverse, rotateSpeed, degrees, false);
    leftBack.spinFor(reverse, rotateSpeed, degrees, false);
    rightFront.spinFor(forward, rotateSpeed, degrees, false);
    rightBack.spinFor(forward, rotateSpeed, degrees);
  }

  VisionSensor.takeSnapshot(VisionSensor__LIKED_CUBE);
  double y = (VisionSensor.largestObject.centerY);
  double upDownSpeed = (Ycenter - y) * 0.1;

  if (y < (Ycenter - OKErrorY)) {
    Brain.Screen.clearLine(1);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("tring to look up  ");
    cameraMotor.spinFor(forward, (upDownSpeed), degrees);
  }
  VisionSensor.takeSnapshot(VisionSensor__LIKED_CUBE);
  y = (VisionSensor.largestObject.centerY);
  upDownSpeed = (Ycenter - y) * 0.1;
  if (y > (Ycenter + OKErrorY)) {
    Brain.Screen.clearLine(1);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("tring to look down");
    cameraMotor.spinFor(forward, (upDownSpeed), degrees);
  }
}

// Looks arround in a clockwise direction looking for the target.
void lookAround(int& forwardBack, int& rotate, int& strafe) {
  // leftFront.spinFor(
  //     forward, 30, degrees,
  //     false); // False makes the robot not wait for the robot to reach teh
  //             // desired position to continue with the code
  // leftBack.spinFor(forward, 30, degrees, false);
  // rightFront.spinFor(reverse, 30, degrees, false);
  // rightBack.spinFor(reverse, 30,
  //                   degrees); // No false means code will not continue until
  //                             // robot reaches desired position
  forwardBack = 0;
  rotate = 30; // 30% rotation speed.
  strafe = 0;
  cameraMotor.spinToPosition(30, degrees);
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("trying to look around");
}

void BackUp() {
  int BackUpDistance = 0;
  BackUpDistance = (800 - DistanceSensor.objectDistance(mm)) * 0.7;
  leftFront.spinFor(reverse, BackUpDistance, degrees, false);
  rightFront.spinFor(reverse, BackUpDistance, degrees, false);
  leftBack.spinFor(reverse, BackUpDistance, degrees, false);
  rightBack.spinFor(reverse, BackUpDistance, degrees);
}

// Used for calibrating linetrackers
void lineTrackerInfo() {
  int fr = FrontRightTracker.reflectivity(pct);
  int fl = FrontLeftTracker.reflectivity(pct);
  int br = BackRightTracker.reflectivity(pct);
  int bl = BackLeftTracker.reflectivity(pct);
  int BackUpDistance = 0;
  const int screenX = 1;
  const int screenY = 3;
  Brain.Screen.setCursor(screenY, screenX);
  Brain.Screen.print("FR: %02d, FL: %02d, BR: %02d, BL: %02d", fr, fl, br, bl);
}

void MoveUp() {
  int MoveUpDistance = 0;
  MoveUpDistance = (DistanceSensor.objectDistance(mm) - 900) * 0.7;
  leftFront.spinFor(forward, MoveUpDistance, degrees, false);
  rightFront.spinFor(forward, MoveUpDistance, degrees, false);
  leftBack.spinFor(forward, MoveUpDistance, degrees, false);
  rightBack.spinFor(forward, MoveUpDistance, degrees);
}

void DistanceInfo() {
  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("%01s", DistanceSensor.isObjectDetected() ? "TRUE" : "FALSE");
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("%01f", DistanceSensor.objectDistance(mm));
}

void lineTrackerInfo(int& forwardBack, int& rotate, int& strafe) {
  bool blTape = isTape(BackLeftTracker.reflectivity());
  bool brTape = isTape(BackRightTracker.reflectivity());
  bool flTape = isTape(FrontLeftTracker.reflectivity());
  bool frTape = isTape(FrontRightTracker.reflectivity());  

  if (blTape && flTape) {
    // Tape on the left side.
    strafe = STRAFE_SPEED_PERCENT;
  }    
}

struct VisionTarget {
  double x;
  double y;
  double distanceFeet;
  bool cubeExists;
};

// void trackColor(signature colorSignature, ){
//   if(VisionSensor.objectCount() == 0){  
//   }

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  int forwardBack;
  int rotate;
  int strafe;
  int x = 0;
  int Xcenter = 150;
  int OKErrorX = 60;
  int rotateSpeed = 0;
  int y = 0;
  int Ycenter = 110;
  int OKErrorY = 50;
  int upDownSpeed = 0;
  leftFront.setVelocity(100, percent);
  leftBack.setVelocity(100, percent);
  rightFront.setVelocity(100, percent);
  rightBack.setVelocity(100, percent);
  cameraMotor.setVelocity(50, percent);
  cameraMotor.setPosition(0, degrees);

  while (1 == 1) {
    Brain.Screen.clearLine(1);
    Brain.Screen.print("%f", cameraMotor.position(degrees));

    VisionSensor.takeSnapshot(VisionSensor__LIKED_CUBE);
    if (VisionSensor.largestObject.exists) {
      detectLikedCube(Xcenter, Ycenter, OKErrorX, OKErrorY);
      lineTrackerInfo();
      DistanceInfo();
      if ((DistanceSensor.objectDistance(mm)) < 800) {
        BackUp();
      }

      if (1700 > (DistanceSensor.objectDistance(mm)) &&
          (DistanceSensor.objectDistance(mm)) > 900) {
        MoveUp();
      }

    } else {
      // Only do this if no other actions.
      lookAround(forwardBack, rotate, strafe);
    }

    // A fail safe so if there is tape detected then the forwardBack, rotate, and strafe values will be altered.
    lineTrackerOverride(forwardBack, rotate, strafe);

    // Drive the chassis according to the final decision
    drive(forwardBack, rotate, strafe);
  }
}
