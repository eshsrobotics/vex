/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Speedbot (4-motor Drivetrain, No Gyro)                    */
/*                                                                            */
/*    Name:                                                                   */
/*    Date:                                                                   */
/*    Class:                                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10, 11, 20
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <memory>    // shared_ptr<T>
#include <algorithm> // std::min, std::max
#include <utility>   // std::move
#include "vex.h"
#include "robot-config.h"
#include "prototypes.h"

using namespace vex;
using std::shared_ptr;
using std::move;
using std::min;
using std::max;

competition Competition;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;

shared_ptr<PivotRampPrototype> getPivotRampPrototype() {
  shared_ptr<PivotRampPrototype> foo;
  if (!foo) {
    const int LEFT_MOTOR_PORT_A = 2 - 1; // left_front_motor
    const int LEFT_MOTOR_PORT_B = 3 - 1; // left_center_motor
    const int LEFT_MOTOR_PORT_C = 4 - 1; // left_back_motor
    const int RIGHT_MOTOR_PORT_A = 5 - 1; // right_front_motor
    const int RIGHT_MOTOR_PORT_B = 20 - 1; // right_center_motor
    const int RIGHT_MOTOR_PORT_C = 7 - 1; // right_back_motor
    const int INTAKE_MOTOR_PORT = 1 - 1;
    const int LIFT_MOTOR_PORT = 9 - 1;
    vex::motor leftMotor1(LEFT_MOTOR_PORT_A);
    vex::motor leftMotor2(LEFT_MOTOR_PORT_B);
    vex::motor leftMotor3(LEFT_MOTOR_PORT_C);
    vex::motor_group leftMotorGroup(leftMotor1, leftMotor2, leftMotor3);

    vex::motor rightMotor1(RIGHT_MOTOR_PORT_A);
    vex::motor rightMotor2(RIGHT_MOTOR_PORT_B);
    vex::motor rightMotor3(RIGHT_MOTOR_PORT_C);
    vex::motor_group rightMotorGroup(rightMotor1, rightMotor2, rightMotor3);
    
    vex::motor intakeMotor1(INTAKE_MOTOR_PORT);
    vex::motor_group intakeMotorGroup(intakeMotor1);

    vex::motor liftMotor1(LIFT_MOTOR_PORT);
    vex::motor_group liftMotorGroup(liftMotor1);

    const double rotationsToTop = 0.5; // TODO: Must be determined experimentally.

    foo = shared_ptr<PivotRampPrototype>
     (new PivotRampPrototype (leftMotorGroup,
                              rightMotorGroup, 
                              intakeMotorGroup, 
                              liftMotorGroup, 
                              rotationsToTop));
  }
  return foo;
}

/**
 * This code block runs before autonomous AND teleop. This code initializes all
 * of the robot's actuators and sensors. We cannot actuate anything as the
 * competition control system blocks us from doing so.
 */
void pre_auton() {
  

}

/**
 * The autonomous routine runs during the first fifteen seconds of the
 * competition.
 */
void autonomous() {  

  intake_roller_motor.spin(vex::directionType::fwd,
                           autonomous_intake_speed_pct,
                           vex::percentUnits::pct);
  
  Drivetrain.setDriveVelocity(autonomous_speed_pct, vex::percentUnits::pct);

  // We do not know whether drive is a blocking-call. If it turns out it is a
  // blocking call, we should use drivefor. The way we would know is that the
  // robot would drive forever.
  Drivetrain.drive(vex::directionType::fwd);
  

  const double start_time_milliseconds = Brain.timer(msec); 

  while (true) {
    double elapsed_time_msec = Brain.timer(msec) - start_time_milliseconds;
    if (elapsed_time_msec > drive_train_duration_ms) {
        Drivetrain.stop();
    }
    if (elapsed_time_msec > intake_motor_duration_ms) {
      intake_roller_motor.stop();
    }
  }
}

/** 
 * The user control section. The code that runs when the driver is in control
 * for remaining 1:45 minutes of the competition.
 */
void teleop() { 
  double liftRotations = 0.0;
  while (true) {
    auto prototype = getPivotRampPrototype();
    prototype->drive(Controller.Axis3.position(percentUnits::pct) / 100.0, 
                     Controller.Axis4.position(percentUnits::pct) / 100.0);

    // // const double SCALE_FACTOR = 0.05;
    // // liftRotations += SCALE_FACTOR * Controller.Axis2.position(percentUnits::pct) / 100.0;
    // // liftRotations = max(0.0, min(liftRotations, 1.0));
    // // prototype.setLiftRotationsDebug(liftRotations);

    // // R2 will be outake and R1 will be intake.
    // if (Controller.ButtonR2.pressing()) {
    //   prototype.intake(1);        
    // } else if (Controller.ButtonR1.pressing()) {
    //   prototype.intake(-1);         
    // } else {
    //   prototype.intake(0);
    // }

  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Register our autonomous and teleop(user control) routines.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(teleop);

  while (true) {
    vex::wait(50, msec);
  }
}