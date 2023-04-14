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

using namespace vex;

signature hatedCube = VisionSensor__GREEN_CUBE;

// Drive is a way to call mechanum so both teliop and autonomus can use it.
// fowardBack is the amount of movement in the foward and back channel a
// positive
// value drives foward a negative drives backwards and 0 stops it.
// rotate is the amount of movement in the turning right and left channel, as
// with
// fowardBack; positive value drives foward a negative drives backwards and 0
// stops it.
// strafe is the amount of movement in the left and rivht channel a positive
// value drives foward a negative drives backwards and 0 stops it.

/*void drive(double fowardBack, double rotate, double strafe) {
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
}*/

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  int fowardBack;
  int rotate;
  int strafe;
  int x = 0;
  int center = 150;
  int OKError = 70;
  int rotateSpeed = 10;
//  while(1==2){
//    leftFront.spinFor(reverse, 10, degrees, false);
//           leftBack.spinFor(reverse, 10, degrees, false);
//           rightFront.spinFor(forward, 10, degrees, false);
//           rightBack.spinFor(forward, 10, degrees);
//  }
  Camera_motor.setPosition(0,degrees);

  while (1 == 1) {
    /*fowardBack = Controller1.Axis3.position();
    rotate = Controller1.Axis1.position();
    strafe = Controller1.Axis4.position();

  leftFront.setVelocity(fowardBack + rotate + strafe, percent);
  rightFront.setVelocity(fowardBack - rotate - strafe, percent);
  leftBack.setVelocity(fowardBack + rotate - strafe, percent);
  rightBack.setVelocity(fowardBack - rotate + strafe, percent);

    //colorHater(fowardBack, rotate, strafe);
    //drive(fowardBack, rotate, strafe);

    leftFront.spin(forward);
    rightFront.spin(forward);
    leftBack.spin(forward);
    rightBack.spin(forward);*/
    VisionSensor.takeSnapshot(VisionSensor__GREEN_CUBE);
    if(VisionSensor.largestObject.exists){
      x = (VisionSensor.largestObject.centerX);

        if(x<(center+OKError)){
          leftFront.spinFor(reverse, rotateSpeed, degrees, false);
          leftBack.spinFor(reverse, rotateSpeed, degrees, false);
          rightFront.spinFor(forward, rotateSpeed, degrees, false);
          rightBack.spinFor(forward, rotateSpeed, degrees);
        }

        if(x>(center-OKError)){
          leftFront.spinFor(forward, rotateSpeed, degrees, false);
          leftBack.spinFor(forward, rotateSpeed, degrees, false);
          rightFront.spinFor(reverse, rotateSpeed, degrees, false);
          rightBack.spinFor(reverse, rotateSpeed, degrees);
        }

    }
  else{
      leftFront.spinFor(forward, 50, degrees, false);
          leftBack.spinFor(forward, 50, degrees, false);
          rightFront.spinFor(reverse, 50, degrees, false);
          rightBack.spinFor(reverse, 50, degrees);
  }
  }

  // int x = 0;
  // int center = 158;// The x coordinate for the center of the vision sensor
  // int OKError = 50; //Used to set a range of values to count is being just in

  //   while(true) {
  //     VisionSensor.takeSnapshot(VisionSensor__GREEN_CUBE);
  //     if (VisionSensor.largestObject.exists)
  //     {
  //       x = VisionSensor.largestObject.centerX;
  //       if(x< (center-OKError)) //If the object is to the left of center
  //       {
  //         RightMotor.spin(directionType::rev, 25, velocityUnits::pct);
  //         LeftMotor.spin(directionType::fwd, 25, velocityUnits::pct);
  //       } else if (x> center + OKError) //If the object is to the right of
  //       center
  //       {
  //         RightMotor.spin(directionType::fwd, 25, velocityUnits::pct);
  //         LeftMotor.spin(directionType::rev, 25, velocityUnits::pct);
  //       } else //The object is not to the right of center and not to the left
  //       of center
  //       {
  //         LeftMotor.stop(brakeType::brake);
  //         RightMotor.stop(brakeType::brake);
  //    }
  // }
  // task::sleep(100);
  // }
  // }
}