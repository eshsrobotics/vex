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

using namespace vex;
using std::min;
using std::max;

enum class PrototypeLiftState {

  // Initial state of the state machine
  // - transitions: unconditional: DEFAULT_LOWEST_HEIGHT
  START,

  // There are some prototypes where the lowest height is the mobile goal height
  // while other robots will have a lower minimum height than the mobile goal
  // level.
  // - transitions:
  //   * X.pressed(): ALLIANCE_STAKE_TRANSITION
  //   * Y.pressed(): WALL_STAKE_TRANSITION
  //   * A.button(): MOBILE_GOAL_TRANSITION
  DEFAULT_LOWEST_HEIGHT,

  // This supports a transition to the lowest height supported by the lift.
  // When transitioning into this state, run the lift in the appropriate direction.
  // - transitions:
  //   * X.pressed(): ALLIANCE_STAKE_TRANSITION
  //   * Y.pressed(): WALL_STAKE_TRANSITION
  //   * A.button(): MOBILE_GOAL_TRANSITION
  //   * lift position = default height: DEFAULT_LOWEST_HEIGHT
  DEFAULT_TRANSITION,

  // This supports a transition to a mobile goal lift height. When transitioning
  // into this state, run the lift in the appropriate direction to reach the
  // desired height.
  // - transitions:
  //   * X.pressed(): ALLIANCE_STAKE_TRANSITION
  //   * Y.pressed(): WALL_STAKE_TRANSITION
  //   * B.pressed(): DEFAULT_TRANSITION
  //   * lift position = mobile goal height: MOBILE_GOAL
  MOBILE_GOAL_TRANSITION,

  // The state where the appropriate lift height for mobile goals is reached.
  // When transitioning into this state, the appropriate height has been
  // reached.
  // - transitions:
  //   * X.pressed(): ALLIANCE_STAKE_TRANSITION
  //   * Y.pressed(): WALL_STAKE_TRANSITION
  //   * B.pressed(): DEFAULT_TRANSITION
  MOBILE_GOAL,

  // The state where the lift is moving in the appropriate direction to reach a
  // height for wall stake intaking. When transitioning into this state, the
  // lift motors will spin in the appropriate direction to reach wall stake height.
  // - transitions:
  //   * X.pressed(): ALLIANCE_STAKE_TRANSITION
  //   * B.pressed(): DEFAULT_TRANSITION
  //   * A.pressed(): MOBILE_GOAL_TRANSITION
  //   * lift position = wall stake height: WALL_STAKE
  WALL_STAKE_TRANSITION,

  // The state after we have reached the appropriate lift height for wall
  // stakes. When transitioning into this state, the WALL_STAKE height has been reached.
  // - transitions:
  //   * X.pressed(): ALLIANCE_STAKE_TRANSITION
  //   * B.pressed(): DEFAULT_TRANSITION
  //   * A.pressed(): MOBILE_GOAL_TRANSITION
  WALL_STAKE,

  // The state where we are transitioning into the appropriate lift height for
  // alliance stakes. When transitioning into this state, the lift motors will
  // spin in the appropriate direction to reach alliance stake height.
  // - transitions:
  //   * Y.pressed(): WALL_STAKE_TRANSITION
  //   * A.pressed(): MOBILE_GOAL_TRANSITION
  //   * B.pressed(): DEFAULT_TRANSITION
  //   * lift position = alliance stake height: ALLIANCE_STAKE
  ALLIANCE_STAKE_TRANSITIONS,

  // The state where we have reached the appropriate lift height for alliance
  // stakes. When transitioning into this state, the appropriate alliance stake
  // height has been reached.
  // - transitions:
  //   * A.pressed(): MOBILE_GOAL_TRANSITION
  //   * B.pressed(): DEFAULT_TRANSITION
  //   * Y.pressed(): WALL_STAKE_TRANSITION
  ALLIANCE_STAKE,
};

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
                       PrototypeIntakeState& currentState);


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
  PrototypeIntakeState currentState = PrototypeIntakeState::START;
  while (true) {
    auto prototype = makePivotRampPrototype();
    prototype.drive(Controller.Axis3.position(percentUnits::pct) / 100,
                    Controller.Axis4.position(percentUnits::pct) / 100);

    const double SCALE_FACTOR = 0.05;
    liftRotations += SCALE_FACTOR * Controller.Axis2.position(percentUnits::pct) / 100.0;
    liftRotations = max(0.0, min(liftRotations, 1.0));
    prototype.setLiftRotationsDebug(liftRotations);

    // Allow the driver to control the direction of any prototype intake.
    updateIntakeState(Controller.ButtonR1.pressing(),
                      Controller.ButtonR2.pressing(),
                      prototype,
                      currentState);
  }
}
void updateIntakeState(bool intakeButton, bool outtakeButton, Iintake& robotWithIntake,
                       PrototypeIntakeState& currentState) {
  // Establishes the control system for any arbitrary prototype intake.
  Brain.Screen.setCursor(3, 10);
  switch (currentState) {
    case PrototypeIntakeState::START:
      robotWithIntake.intake(0);
      currentState = PrototypeIntakeState::STOPPED;
      Brain.Screen.print("START");
      break;

    case PrototypeIntakeState::STOPPED:
      if (intakeButton && !outtakeButton) {
        currentState = PrototypeIntakeState::INTAKING;
        robotWithIntake.intake(1);
        Brain.Screen.print("INTAKING");
      } else if (!intakeButton && outtakeButton) {
        currentState = PrototypeIntakeState::OUTTAKING;
        robotWithIntake.intake(-1);
        Brain.Screen.print("OUTTAKING");
      }
      break;

    case PrototypeIntakeState::INTAKING:
      if (!intakeButton) {
        currentState = PrototypeIntakeState::STOPPED;
        robotWithIntake.intake(0);
        Brain.Screen.print("STOPPED");
      }
      break;

    case PrototypeIntakeState::OUTTAKING:
      if (!outtakeButton) {
        currentState = PrototypeIntakeState::STOPPED;
        robotWithIntake.intake(0);
        Brain.Screen.print("STOPPED");
      }
      break;

  };

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