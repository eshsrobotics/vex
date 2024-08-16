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

#include "robot-config.h"
#include "prototypes.h"
#include "vex.h"

#include <algorithm> // std::min, std::max
#include "updateLiftState.h"

using namespace vex;
using std::min;
using std::max;

enum class PrototypeIntakeState {

  // Initial state of the state machine
  // - transitions: default (unconditional)
  START,

  // The state when the prototype is not moving: the default state.
  // - transitions:
  //   * R1.pressed() == true: INTAKING
  //   * R2.pressed() == true: OUTTAKING
  //   * else: STOPPED
  STOPPED,

  // The state when the prototype is intaking.
  // - transitions:
  //   * R1.pressed() == false: STOPPED
  INTAKING,

  // The state when the prototype is outaking.
  // - transitions:
  //   * R2.pressed() == false: OUTTAKING
  OUTTAKING,

};
void updateIntakeState(bool intakeButton, bool outtakeButton, Iintake& robotWithIntake,
                       PrototypeIntakeState& state);

/**
 * Moves the lift directly to determine rotationsToTop.
 * @param buttonUp button for making the lift go up
 * @param buttonDown button for making the lift go down
 * @param robotWithLift a robot inheriting from Ilift
 * @param rotationsPerButton the number of rotations the motor makes
 */
void moveLiftRotationsToTopDebug(bool buttonUp, bool buttonDown, Ilift& robotWithLift) {
  const double rotationsPerButton = 0.5;
  if (buttonUp) {
      robotWithLift.moveLiftDirect(rotationsPerButton);
  } else if (buttonDown) {
      robotWithLift.moveLiftDirect(-rotationsPerButton);
  } else {
    robotWithLift.moveLiftDirect(0);
  }
}


void moveLiftGatherHeightsDebug(bool buttonUp, bool buttonDown, Ilift& robotWithLift) {
  const double incrementPerButton = 0.05;
  // There is no else as the setLiftPosition() call moves the lift to the
  // desired position until reached, then stops.
  if (buttonUp) {
    robotWithLift.setLiftPosition(robotWithLift.getliftPosition() + incrementPerButton);
  } else if (buttonDown) {
    robotWithLift.setLiftPosition(robotWithLift.getliftPosition() - incrementPerButton);
  }

}

competition Competition;

PivotRampPrototype makePivotRampPrototype() {
  const int LEFT_MOTOR_PORT_A = 2 - 1;
  const int LEFT_MOTOR_PORT_B = 3 - 1;
  const int LEFT_MOTOR_PORT_C = 4 - 1 ;
  const int RIGHT_MOTOR_PORT_A = 5 - 1;
  const int RIGHT_MOTOR_PORT_B = 6 - 1;
  const int RIGHT_MOTOR_PORT_C = 7 - 1;
  const int INTAKE_MOTOR_PORT = 8 - 1;
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

  PivotRampPrototype pivotRampPrototypeObject(leftMotorGroup,
                                              rightMotorGroup,
                                              intakeMotorGroup,
                                              liftMotorGroup,
                                              rotationsToTop);
  return pivotRampPrototypeObject;
}

FlywheelPrototype makeFlywheelPrototype() {
  // The ports are supposed to be changed when actually building. Different
  // prototypes will have different ports based on physical needs.
  const int LEFT_MOTOR_PORT_A = 2 - 1;
  const int LEFT_MOTOR_PORT_B = 3 - 1;
  const int LEFT_MOTOR_PORT_C = 4 - 1 ;
  const int RIGHT_MOTOR_PORT_A = 5 - 1;
  const int RIGHT_MOTOR_PORT_B = 6 - 1;
  const int RIGHT_MOTOR_PORT_C = 7 - 1;
  const int LEFT_FLYWHEEL_PORT = 8 - 1;
  const int RIGHT_FLYWHEEL_PORT = 9 - 1;

  vex::motor leftMotor1(LEFT_MOTOR_PORT_A);
  vex::motor leftMotor2(LEFT_MOTOR_PORT_B);
  vex::motor leftMotor3(LEFT_MOTOR_PORT_C);
  vex::motor_group leftMotorGroup(leftMotor1, leftMotor2, leftMotor3);

  vex::motor rightMotor1(RIGHT_MOTOR_PORT_A);
  vex::motor rightMotor2(RIGHT_MOTOR_PORT_B);
  vex::motor rightMotor3(RIGHT_MOTOR_PORT_C);
  vex::motor_group rightMotorGroup(rightMotor1, rightMotor2, rightMotor3);

  // TODO: Make sure the left and the right flywheel motors are spinning in
  // opposite directions.
  vex::motor leftFlywheelMotor(LEFT_FLYWHEEL_PORT);
  vex::motor rightFlywheelMotor(RIGHT_FLYWHEEL_PORT);
  vex::motor_group intakeMotorGroup(leftFlywheelMotor, rightFlywheelMotor);

  return FlywheelPrototype(leftMotorGroup, rightMotorGroup, intakeMotorGroup);
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

  // intake_roller_motor.spin(vex::directionType::fwd,
  //                          autonomous_intake_speed_pct,
  //                          vex::percentUnits::pct);
  // Drivetrain.setDriveVelocity(autonomous_speed_pct, vex::percentUnits::pct);

  // // We do not know whether drive is a blocking-call. If it turns out it is a
  // // blocking call, we should use drivefor. The way we would know is that the
  // // robot would drive forever.
  // Drivetrain.drive(vex::directionType::fwd);

  // const double start_time_milliseconds = Brain.timer(msec);

  // while (true) {
  //   double elapsed_time_msec = Brain.timer(msec) - start_time_milliseconds;
  //   if (elapsed_time_msec > experiment_duration_ms) {
  //       Drivetrain.stop();
  //       intake_roller_motor.stop();
  //   }
  // }
}

/**
 * The user control section. The code that runs when the driver is in control
 * for remaining 1:45 minutes of the competition.
 */
void teleop() {
  double liftRotations = 0.0;
  PrototypeIntakeState intakeState = PrototypeIntakeState::START;
  LiftState liftState = INITIAL_LIFT_STATE;
  while (true) {
    auto prototype = makePivotRampPrototype();
    prototype.drive(Controller.Axis3.position(percentUnits::pct) / 100,
                    Controller.Axis4.position(percentUnits::pct) / 100);

    // Allow the driver to control the direction of any prototype intake.
    updateIntakeState(Controller.ButtonR1.pressing(),
                      Controller.ButtonR2.pressing(),
                      prototype,
                      intakeState);

    // Allow the driver to control the lift positi-on.
    bool buttonUp = Controller.ButtonL1.pressing();
    bool buttonDown = Controller.ButtonL2.pressing();

    // The functions below are mutually exclusive. We have two ways of moving
    // the lift, one directly and one direction.
    //
    // * The first function moves the lift directly to determine rotationsToTop.
    // * The second function moves the lift directly to determine the other
    //   heights after having determined the rotationsToTop.
    // * The third function calls the production state machine functions but
    //   requires all the heights identified.
    moveLiftRotationsToTopDebug(buttonUp, buttonDown, prototype); // move lift directly (rotationsToTop)
    // moveLiftGatherHeightsDebug(buttonUp, buttonDown, prototype); // move lift directly (relative heights)
    // updateLiftState(buttonUp, buttonDown, prototype, liftState); // move lift by state machine (final)
  }
}

/**
 * We have three states for our state machine: STOPPED, INTAKING, and OUTAKING.
 * This helper handles that for us. Call it once per frame and it will set the
 * state.
 *
 * @param intakeButton true if the caller wants to intake and false if they do
 * not.
 * @param outtakeButton true if the caller wants to outtake and false if they do
 *                      not. If both are of the same value, it is ignored.
 * @param robotWithIntake a prototype that we can instruct it to intake
 * @param state[out] Whenever we change states in our state machine, we
 * override the previous value of state. We do not own state.
 */
void updateIntakeState(bool intakeButton, bool outtakeButton, Iintake& robotWithIntake,
                       PrototypeIntakeState& state) {
  // Establishes the control system for any arbitrary prototype intake.
  Brain.Screen.setCursor(3, 10);
  switch (state) {
    case PrototypeIntakeState::START:
      robotWithIntake.intake(0);
      state = PrototypeIntakeState::STOPPED;
      Brain.Screen.print("START");
      break;

    case PrototypeIntakeState::STOPPED:
      if (intakeButton && !outtakeButton) {
        state = PrototypeIntakeState::INTAKING;
        robotWithIntake.intake(1);
        Brain.Screen.print("INTAKING");
      } else if (!intakeButton && outtakeButton) {
        state = PrototypeIntakeState::OUTTAKING;
        robotWithIntake.intake(-1);
        Brain.Screen.print("OUTTAKING");
      }
      break;

    case PrototypeIntakeState::INTAKING:
      if (!intakeButton) {
        state = PrototypeIntakeState::STOPPED;
        robotWithIntake.intake(0);
        Brain.Screen.print("STOPPED");
      }
      break;

    case PrototypeIntakeState::OUTTAKING:
      if (!outtakeButton) {
        state = PrototypeIntakeState::STOPPED;
        robotWithIntake.intake(0);
        Brain.Screen.print("STOPPED");
      }
      break;
  };
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Register our autonomous and teleop(user control) routines. The Competition
  // functions are O1 do not actually run autonomous or teleop. That
  // responsibility lies somewhere else.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(teleop);

  while (true) {
    vex::wait(50, msec);
  }
}