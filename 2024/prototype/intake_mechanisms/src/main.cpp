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

#include <algorithm> // std::min, std::max
#include <vector>
#include <string>

#include "robot-config.h"
#include "prototypes.h"
#include "vex.h"
#include "updateLiftState.h"
#include "autonomous_task_tree.h"

using namespace vex;
using std::min;
using std::max;
using std::vector;
using std::make_shared;

// This is global temporary so we can test whether the digital_out::value()
// method works for the digital solenoid the way we think it works. This is
// really supposed to be inside the factory.
digital_out pneumaticClamp(DOUBLE_SOLENOID_PORT);

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
  const int LEFT_MOTOR_PORT_A = 4 - 1; // left_front_motor
  const int LEFT_MOTOR_PORT_B = 5 - 1; // left_bottom_motor
  const int LEFT_MOTOR_PORT_C = 6 - 1; // left_top_motor
  const int RIGHT_MOTOR_PORT_A = 1 - 1; // right_top_motor
  const int RIGHT_MOTOR_PORT_B = 2 - 1; // right_bottom_motor
  const int RIGHT_MOTOR_PORT_C = 3 - 1; // right_top_motor
  const int INTAKE_MOTOR_PORT = 8 - 1;
  const int LIFT_MOTOR_PORT = 9 - 1;

  vex::motor leftMotor1(LEFT_MOTOR_PORT_A);
  vex::motor leftMotor2(LEFT_MOTOR_PORT_B);
  vex::motor leftMotor3(LEFT_MOTOR_PORT_C);
  vector<motor> leftMotors = {leftMotor1, leftMotor2, leftMotor3};

  vex::motor rightMotor1(RIGHT_MOTOR_PORT_A);
  vex::motor rightMotor2(RIGHT_MOTOR_PORT_B);
  vex::motor rightMotor3(RIGHT_MOTOR_PORT_C);
  vector<motor> rightMotors = {rightMotor1, rightMotor2, rightMotor3};

  vex::motor intakeMotor1(INTAKE_MOTOR_PORT);
  vector<motor> intakeMotors = {intakeMotor1};

  vex::motor liftMotor1(LIFT_MOTOR_PORT);
  vector<motor> liftMotors = {liftMotor1};

  const double rotationsToTop = 0.5; // TODO: Must be determined experimentally.

  PivotRampPrototype p(leftMotors,
                       rightMotors,
                       intakeMotors,
                       liftMotors,
                       rotationsToTop,
                       pneumaticClamp);
  p.setLiftHeights({
    // Update these values once rotationsToTop has been determined.
    .defaultHeight=0,
    .mobileGoalHeight=0,
    .allianceStakeHeight=0,
    .wallStakeHeight=0
  });
  return p;
}

/**
 * Encapsulates all clamping functionality for teleop in one easy-to-use wrapper
 * function.
 * @param p a reference to a ImobileGoalIntake instance
*/
void updateClampState(ImobileGoalIntake& p) {
  bool clamp = Controller.ButtonUp.pressing();
  bool unclamp = Controller.ButtonDown.pressing();
  if (clamp) {
    p.clamp(true);
  } else if (unclamp) {
    p.clamp(false);
  }
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
  auto prototype = makePivotRampPrototype();
  const double autonomous_drive_speed = 1;
  const double autonomous_intake_speed = 1;
  const double experiment_duration_ms = 5000;

  auto rootTask = make_shared<WaitMillisecondsTask>(0);
  auto driveMillisecondsTask =
    make_shared<DriveMillisecondsTask>(prototype, experiment_duration_ms, autonomous_drive_speed
                                       );
  auto intakeMillisecondsTask =
    make_shared<IntakeMillisecondsTask>(prototype,
                                        experiment_duration_ms,
                                        autonomous_intake_speed);
  // auto testDriveTask = make_shared<TestDriveTask>(10, prototype);
  // addTask(rootTask, testDriveTask);
  execute(rootTask);
}

/**
 * The user control section. The code that runs when the driver is in control
 * for remaining 1:45 minutes of the competition.
 */
void teleop() {
  PrototypeIntakeState intakeState = PrototypeIntakeState::START;
  LiftState liftState = INITIAL_LIFT_STATE;
  Brain.Screen.clearScreen();
  Controller.Screen.clearScreen();
  while (true) {
    auto prototype = makePivotRampPrototype();
    prototype.drive(Controller.Axis3.position(percentUnits::pct) / 100.0,
                    Controller.Axis1.position(percentUnits::pct) / 100.0);

    // Allow the driver to control the direction of any prototype intake.
    updateIntakeState(Controller.ButtonR2.pressing(),
                      Controller.ButtonR1.pressing(),
                      prototype,
                      intakeState);

    // Allows controlling the mobile goal clamp.
    updateClampState(prototype);

    // // Allow the driver to control the lift position.
    // bool buttonUp = Controller.ButtonL1.pressing();
    // bool buttonDown = Controller.ButtonL2.pressing();

    // // The functions below are mutually exclusive. We have two ways of moving
    // // the lift, one directly and one direction.
    // //
    // // * The first function moves the lift directly to determine rotationsToTop.
    // // * The second function moves the lift directly to determine the other
    // //   heights after having determined the rotationsToTop.
    // // * The third function calls the production state machine functions but
    // //   requires all the heights identified.
    // moveLiftRotationsToTopDebug(buttonUp, buttonDown, prototype); // move lift directly (rotationsToTop)
    // moveLiftGatherHeightsDebug(buttonUp, buttonDown, prototype); // move lift directly (relative heights)
    // updateLiftState(buttonUp, buttonDown, prototype, liftState); // move lift by state machine (final)
    Brain.Screen.setCursor(BRAIN_CLAMP_VALUE_ROW, 1);
    Brain.Screen.print("clamp value: %d", pneumaticClamp.value());
    vex::wait(50, msec);
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
  const char* format = "Next State: %s        ";
  const char* label = "";
  Brain.Screen.setCursor(3, 10);
  switch (state) {
    case PrototypeIntakeState::START:
      robotWithIntake.intake(0);
      state = PrototypeIntakeState::STOPPED;
      label = "Start";
      break;

    case PrototypeIntakeState::STOPPED:
      if (intakeButton && !outtakeButton) {
        state = PrototypeIntakeState::INTAKING;
        robotWithIntake.intake(-1);
        label = "Intaking";
      } else if (!intakeButton && outtakeButton) {
        state = PrototypeIntakeState::OUTTAKING;
        robotWithIntake.intake(1);
        label = "Outtaking";
      }
      break;

    case PrototypeIntakeState::INTAKING:
      if (!intakeButton) {
        state = PrototypeIntakeState::STOPPED;
        robotWithIntake.intake(0);
        label = "Stopped";
      }
      break;

    case PrototypeIntakeState::OUTTAKING:
      if (!outtakeButton) {
        state = PrototypeIntakeState::STOPPED;
        robotWithIntake.intake(0);
        label = "Stopped";
      }
      break;
  };

  if (strlen(label) > 0) {
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print(format, label);
  }
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