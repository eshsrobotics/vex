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
  const double rotationsPerButton = 10;
  static double rotations = 0;

  // The lift moves UP if buttonDown is pressed, so the signs are reversed
  // for buttonUp and buttonDown.
  if (buttonUp) {
      robotWithLift.moveLiftDirect(rotationsPerButton);
      rotations -= rotationsPerButton;
  } else if (buttonDown) {
      robotWithLift.moveLiftDirect(-rotationsPerButton);
      rotations += rotationsPerButton;
  } else {
    robotWithLift.moveLiftDirect(0);
  }
  Controller.Screen.setCursor(CONTROLLER_LIFT_POSITION_ROW, 1);
  Controller.Screen.print("Lift at %.2f revs ",
                          rotations);
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
  Controller.Screen.setCursor(CONTROLLER_LIFT_POSITION_ROW, 1);
  Controller.Screen.print(robotWithLift.getliftPosition() * 100);
}

competition Competition;

PivotRampPrototype makePivotRampPrototype() {
  const int LEFT_MOTOR_PORT_A = 15 - 1; // left_front_motor
  const int LEFT_MOTOR_PORT_B = 16 - 1; // left_bottom_motor
  const int LEFT_MOTOR_PORT_C = 14 - 1; // left_top_motor
  const int RIGHT_MOTOR_PORT_A = 12 - 1; // right_top_motor
  const int RIGHT_MOTOR_PORT_B = 13 - 1; // right_bottom_motor
  const int RIGHT_MOTOR_PORT_C = 11 - 1; // right_top_motor
  const int INTAKE_MOTOR_PORT_A = 18 - 1;
  const int INTAKE_MOTOR_PORT_B = 1 - 1;
  const int LIFT_MOTOR_PORT = 9 - 1;

  vex::motor leftMotor1(LEFT_MOTOR_PORT_A);
  vex::motor leftMotor2(LEFT_MOTOR_PORT_B);
  vex::motor leftMotor3(LEFT_MOTOR_PORT_C, true);
  vector<motor> leftMotors = {leftMotor1, leftMotor2, leftMotor3};

  vex::motor rightMotor1(RIGHT_MOTOR_PORT_A);
  vex::motor rightMotor2(RIGHT_MOTOR_PORT_B);
  vex::motor rightMotor3(RIGHT_MOTOR_PORT_C, true);
  vector<motor> rightMotors = {rightMotor1, rightMotor2, rightMotor3};

  vex::motor intakeMotor1(INTAKE_MOTOR_PORT_A);
  vex::motor intakeMotor2(INTAKE_MOTOR_PORT_B);
  vector<motor> intakeMotors = {intakeMotor1, intakeMotor2};

  vex::motor liftMotor1(LIFT_MOTOR_PORT);
  vector<motor> liftMotors = {liftMotor1};

  const double rotationsToTop = 1.5; //This value has been determined experimentally.

  vex::triport::port DOUBLE_SOLENOID_PORT = Seventeen59A.ThreeWirePort.C;
  digital_out pneumaticClamp(DOUBLE_SOLENOID_PORT);

  vex::triport::port CLIMB_PORT = Seventeen59A.ThreeWirePort.G;
  digital_out pneumaticClimb(CLIMB_PORT);

  vex::triport::port DOINKER_PORT = Seventeen59A.ThreeWirePort.D;
  digital_out pneumaticDoinker(DOINKER_PORT);

  vex::triport::port SWITCH_PORT = Seventeen59A.ThreeWirePort.B;
  vex::limit limitSwitch(SWITCH_PORT);

  PivotRampPrototype p(leftMotors,
                       rightMotors,
                       intakeMotors,
                       liftMotors,
                       rotationsToTop,
                       pneumaticClamp,
                       pneumaticDoinker,
                       limitSwitch);
  p.setLiftHeights({
    // These values have been determined experimentally.
    .defaultHeight = 0,
    .mobileGoalHeight = 0.231,
    .allianceStakeHeight = rotationsToTop,
    .wallStakeHeight = 1.3
  });
  return p;
}

/**
 * Encapsulates mobile goal clamping functionality for teleop in one easy-to-use wrapper
 * function.
 * @param p a reference to a ImobileGoalIntake instance 
*/
void updateClampState(ImobileGoalIntake& p) {
  bool clamp = Controller.ButtonL2.pressing(); //means the air is released
  bool unclamp = Controller.ButtonL1.pressing(); //means the air is pumped in
  if (clamp) {
    p.clamp(true);
  } else if (unclamp) {
    p.clamp(false);
  }
}
/**
 * Encapsulates doinker functionality for teleop in one function.
 * @param p a reference to an Iclimb instance (the prototype)
 */
void updateDoinkerState(Iclimb& p) {
  bool buttonDown = Controller.ButtonX.pressing();
  bool buttonUp = Controller.ButtonY.pressing();

  if (buttonDown) {
    p.activateClimb(true);
  }
  if (buttonUp) {
    p.activateClimb(false);
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
  vex::inertial inertialSensor(INERTIAL_PORT);

  // auto fullAutonRootTask = make_shared<WaitMillisecondsTask>(0);
  // auto B = make_shared<DriveStraightTask>(-0.4572 * 100, prototype);
  // auto C = make_shared<MobileGoalIntakeTask>(prototype, true);
  // auto D = make_shared<TurnTask>(94.7, gyro, prototype);
  // auto E = make_shared<DriveStraightTask>(0.22 * 100, prototype);
  // auto F = make_shared<IntakeMillisecondsTask>(prototype, 1e5);
  // auto G = make_shared<IntakeMillisecondsTask>(prototype, 67.96);
  // auto H = make_shared<DriveStraightTask>(0.2 * 100, prototype);
  // auto I = make_shared<TurnTask>(65.01, gyro, prototype);
  // auto J = make_shared<MobileGoalIntakeTask>(prototype, false);
  // auto K = make_shared<DriveStraightTask>(1.37 * 100, prototype);
  // auto L = make_shared<IntakeMillisecondsTask>(prototype, 0.5);
  // auto M = make_shared<TurnTask>(8.57, gyro, prototype);
  // auto N = make_shared<DriveStraightTask>(-0.225 * 100, prototype);
  // auto O = make_shared<MobileGoalIntakeTask>(prototype, true);
  // auto P = make_shared<IntakeMillisecondsTask>(prototype, 1e5);
  // auto Q = make_shared<TurnTask>(-3.83, gyro, prototype);
  // auto R = make_shared<DriveStraightTask>(-0.236 * 100, prototype);

  // // Leg 1: Moving backwards to the first Mobile Goal.
  // addTask(fullAutonRootTask, B);
  // addTask(B, C);
  // addTask(C, D);

  // // Leg 2: Driving and score the first set of rings.
  // addTask(D, E);
  // addTask(D, F);
  // addTask(E, G);

  // // Leg 3: Driving and scoring one of the cluster of 8 rings.
  // addTask(G, H);
  // addTask(H, I);
  // addTask(I, J);

  // // Leg 4: The long drive from the driver's left to the driver's right and
  // // scoring a ring from a right-side stack.
  // addTask(I, K);
  // addTask(K, L);
  // addTask(L, M);

  // // Leg 5: Grabbing a mobile goal to score the rings intaked in Leg 4.
  // addTask(M, N);
  // addTask(N, O);
  // addTask(O, P);
  // addTask(O, Q);

  // // Leg 6: Driving forward to reach the wall and scoring the autonomous win point.
  // addTask(Q, R);
  
  // This trajectory works only on the red negative corner
  auto REDNegative = make_shared<WaitMillisecondsTask>(0);
  auto A1 = make_shared<DriveStraightTask>(-80, prototype);
  auto B1 = make_shared<MobileGoalIntakeTask>(prototype, true);
  auto C1 = make_shared<IntakeMillisecondsTask>(prototype, 5000, -1);
  auto D1 = make_shared<GoodTurnTask>(45, prototype);
  auto E1 = make_shared<DriveStraightTask>(50, prototype);
  auto F1 = make_shared<GoodTurnTask>(190, prototype);
  auto G1 = make_shared<DriveStraightTask>(100, prototype);

  auto BLUENegative = make_shared<WaitMillisecondsTask>(0);
  auto A3 = make_shared<DriveStraightTask>(-80, prototype);
  auto B3 = make_shared<MobileGoalIntakeTask>(prototype, true);
  auto C3 = make_shared<IntakeMillisecondsTask>(prototype, 7000, -1);
  auto D3 = make_shared<GoodTurnTask>(-45, prototype);
  auto E3 = make_shared<DriveStraightTask>(50, prototype);
  auto F3 = make_shared<GoodTurnTask>(-190, prototype);
  auto G3 = make_shared<DriveStraightTask>(100, prototype);

  // This trajectory works only on the red positive corner
  auto REDgoalRushPositiveRootTask = make_shared<WaitMillisecondsTask>(0);
  auto A = make_shared<DriveStraightTask>(65, prototype);
  auto B = make_shared<IntakeMillisecondsTask>(prototype, 600, -1);
  auto C = make_shared<DriveStraightTask>(60, prototype);
  auto D = make_shared<DriveStraightTask>(-30, prototype);
  auto E = make_shared<GoodTurnTask>(-33, prototype);
  auto F = make_shared<DriveStraightTask>(37, prototype);
  auto G = make_shared<DeployDoinkerTask>(prototype, true);
  auto H = make_shared<WaitMillisecondsTask>(100);
  auto I = make_shared<DriveStraightTask>(-60, prototype);
  auto J = make_shared<GoodTurnTask>(60, prototype);
  auto K = make_shared<DeployDoinkerTask>(prototype, false);
  auto L = make_shared<GoodTurnTask>(40, prototype);
  auto M = make_shared<DriveStraightTask>(-80, prototype);
  auto N = make_shared<MobileGoalIntakeTask>(prototype, true); 
  auto O = make_shared<IntakeMillisecondsTask>(prototype, 2500, -1);
  auto P = make_shared<DriveStraightTask>(70, prototype);

auto BLUEgoalRushPositiveRootTask = make_shared<WaitMillisecondsTask>(0);
  auto A2 = make_shared<DriveStraightTask>(60, prototype);
  auto B2 = make_shared<IntakeMillisecondsTask>(prototype, 500, -1);
  auto C2 = make_shared<DriveStraightTask>(60, prototype);
  auto D2 = make_shared<DeployDoinkerTask>(prototype, true);
  auto E2 = make_shared<WaitMillisecondsTask>(100);
  auto F2 = make_shared<DriveStraightTask>(-90, prototype);
  auto G2 = make_shared<GoodTurnTask>(-120, prototype);
  auto H2 = make_shared<DeployDoinkerTask>(prototype, false);
  auto I2 = make_shared<GoodTurnTask>(-40, prototype);
  auto J2 = make_shared<DriveStraightTask>(-70, prototype);
  auto K2 = make_shared<MobileGoalIntakeTask>(prototype, true); 
  auto L2 = make_shared<IntakeMillisecondsTask>(prototype, 4500, -1);
  auto M2 = make_shared<GoodTurnTask>(-100, prototype);
  auto N2 = make_shared<DriveStraightTask>(40, prototype);


  // auto intakeTask = make_shared <IntakeMillisecondsTask>(prototype, 1000, 1);
  // auto driveBack = make_shared<DriveStraightTask>(10, prototype);

  auto testRootTask = make_shared<WaitMillisecondsTask>(0);
  auto testTurn = make_shared<GoodTurnTask>(90, prototype);

  addTask(REDNegative, A1);
  addTask(A1, B1);
  addTask(B1, C1);
  addTask(B1, D1);
  addTask(D1, E1);
  addTask(E1, F1);
  addTask(F1, G1);

  addTask(BLUENegative, A3);
  addTask(A3, B3);
  addTask(B3, C3);
  addTask(B3, D3);
  addTask(D3, E3);
  addTask(E3, F3);
  addTask(F3, G3);

  addTask(REDgoalRushPositiveRootTask, A);
  addTask(A, B);
  addTask(A, C);
  addTask(C, D);
  addTask(D, E);
  addTask(E, F);
  addTask(F, G);
  addTask(G, H);
  addTask(H, I);
  addTask(I, J);
  addTask(J, K);
  addTask(J, L);
  addTask(L, M);
  addTask(M, N);
  addTask(M, O);

  addTask(BLUEgoalRushPositiveRootTask, A2);
  addTask(A2, B2);
  addTask(A2, C2);
  addTask(C2, D2);
  addTask(D2, E2);
  addTask(E2, F2);
  addTask(F2, G2);
  addTask(G2, H2);
  addTask(G2, I2);
  addTask(I2, J2);
  addTask(J2, K2);
  addTask(K2, L2);
  addTask(K2, M2);
  addTask(M2, N2);


  addTask(testRootTask, testTurn);

  // execute(fullAutonRootTask);
  execute(REDgoalRushPositiveRootTask);
 // execute(BLUEgoalRushPositiveRootTask);
 // execute(REDNegative);          //Michal Look Here
  // execute(BLUENegative);       
  // execute(testRootTask);
}

/**
 * The user control section. The code that runs when the driver is in control
 * for remaining 1:45 minutes of the competition.
 */
void teleop() {
  PrototypeIntakeState intakeState = PrototypeIntakeState::START;
  LiftState liftState = INITIAL_LIFT_STATE;
  Seventeen59A.Screen.clearScreen();
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

    // Allows controlling the climb hooks.
    updateDoinkerState(prototype);

    // // Allow the driver to control the lift position.
    bool buttonUp = Controller.ButtonUp.pressing();
    bool buttonDown = Controller.ButtonDown.pressing();
    //moveLiftGatherHeightsDebug(Controller.ButtonL1.pressing(), Controller.ButtonL2.pressing(), prototype);
   
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
    updateLiftState(buttonUp, buttonDown, prototype, liftState); // move lift by state machine (final)

    Seventeen59A.Screen.setCursor(BRAIN_CLAMP_VALUE_ROW, 1);
    Seventeen59A.Screen.print("clamp value: %d", prototype.pneumaticClamp.value());
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
 * @param state [out] Whenever we change states in our state machine, we
 * override the previous value of state. We do not own state.
 */
void updateIntakeState(bool intakeButton, bool outtakeButton, Iintake& robotWithIntake,
                       PrototypeIntakeState& state) {
  // Establishes the control system for any arbitrary prototype intake.
  const char* format = "Next State: %s        ";
  const char* label = "";
  Seventeen59A.Screen.setCursor(3, 10);
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