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
// ---- END VEXCODE CONFIGURED DEVICES ----
// Controller1          controller

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

void deployCubes();

bool sneak = false;
bool deployingCubes = false;

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


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;


const double SNEAK_PERCENTAGE = 0.50;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // Enough with the slow motors out of the box already!
  IntakeLift.setVelocity(100, percent);
  LeftIntake.setVelocity(100, percent);
  RightIntake.setVelocity(100, percent);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  // Drive the robot forward for a few seconds, then drive back.
  mecanumDrive(0, 0, 100);
  const int DRIVE_TIME_MILISECONDS = 500;
  wait(DRIVE_TIME_MILISECONDS, msec);
  mecanumDrive(0, 0, -100);
  wait(DRIVE_TIME_MILISECONDS, msec);

  // Done.
  FrontLeftWheel.stop();
  FrontRightWheel.stop();
  BackLeftWheel.stop();
  BackRightWheel.stop();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  // This is the main execution loop for the user control program.
  // Each time through the loop your program should update motor + servo
  // values based on feedback from the joysticks.
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
    } else if (!deployingCubes) {
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
    } else if (Controller1.ButtonR1.pressing()) {
      IntakeLift.spin(reverse);
    } else if (!deployingCubes) {
      bool waitForCompletion = false;
      IntakeLift.spinToPosition(IntakeLift.position(degrees), degrees, waitForCompletion);
    }

    Controller1.ButtonA.pressed([] () {
      if (!deployingCubes) {
        deployCubes();
      }
    });



    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  } // end (loop forever)
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
}

void deployCubes() {
  deployingCubes = true;

  // The order of events is:
  // (1) Push the tray
  // (2) Right before the tray is fully pushed, lift the intake and start reversing the intake motors
  // (3) Stop the intake lift and back off while the intake motors are still hot
  // (4) Stop the intake motors and return the tray and lift to start position
  const double TRAY_PUSH_START_SECONDS = 0.0;
  const double TRAY_PUSH_DURATION_SECONDS = 5.0;
  const double TRAY_SPEED_PERCENT = 25.0;

  const double INTAKE_LIFT_START_SECONDS = 1.0;
  const double INTAKE_LIFT_DURATION_SECONDS = 3.0;
  const double INTAKE_LIFT_SPEED_PERCENT = 20.0;

  const double INTAKE_SPEED_PERCENT = 25.0;

  const double BACKOFF_START_SECONDS = 5.0;
  const double BACKOFF_DURATION_SECONDS = 3.0;
  const double BACKOFF_SPEED_PERCENT = 100.0;

  // Set initial velocities
  IntakeLift.setVelocity(INTAKE_LIFT_SPEED_PERCENT, percent);
  TrayPusher.setVelocity(TRAY_SPEED_PERCENT, percent);
  LeftIntake.setVelocity(INTAKE_SPEED_PERCENT, percent);
  RightIntake.setVelocity(INTAKE_SPEED_PERCENT, percent);

  double startTimeMilliseconds = Brain.timer(msec);
  while (true) {

    double elapsedTimeSeconds = (Brain.timer(msec) - startTimeMilliseconds) / 1000.0;
    bool trayDone = false, liftDone = false, driveDone = false;

    ///////////////////
    // MOVE THE TRAY //
    ///////////////////

    if (elapsedTimeSeconds > TRAY_PUSH_START_SECONDS &&
        elapsedTimeSeconds < TRAY_PUSH_START_SECONDS + TRAY_PUSH_DURATION_SECONDS) {

      // Push the tray out.
      TrayPusher.spin(reverse);

    } else if (elapsedTimeSeconds > BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS &&
               elapsedTimeSeconds < BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS + TRAY_PUSH_DURATION_SECONDS) {

      // Return the tray to position.
      TrayPusher.spin(forward);

    } else {

      TrayPusher.stop();
      trayDone = true;
    }

    //////////////////////////
    // MOVE THE INTAKE LIFT //
    //////////////////////////

    if (elapsedTimeSeconds > INTAKE_LIFT_START_SECONDS &&
        elapsedTimeSeconds < INTAKE_LIFT_START_SECONDS + INTAKE_LIFT_DURATION_SECONDS) {

      IntakeLift.spin(forward);

      // Start the intake motors here.
      LeftIntake.spin(reverse);
      RightIntake.spin(forward);

    } else if (elapsedTimeSeconds > BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS &&
               elapsedTimeSeconds < BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS + INTAKE_LIFT_DURATION_SECONDS) {

      // Return the intake lift to position...gently.
      IntakeLift.setVelocity(INTAKE_LIFT_SPEED_PERCENT * 0.1, percent);
      IntakeLift.spin(reverse);

    } else {

      IntakeLift.stop();
      liftDone = true;
    }

    ////////////////////
    // MOVE THE DRIVE //
    ////////////////////

    if (elapsedTimeSeconds > BACKOFF_START_SECONDS &&
        elapsedTimeSeconds < BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS) {

      // Back away.
      //
      // Yeah, the channels are still flipped.
      mecanumDrive(0, 0, -100);

    } else {
      // Stop the drive.
      mecanumDrive(0, 0, 0);
      driveDone = true;
    }

    // Are we finished?
    if (elapsedTimeSeconds > BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS) {
      // Stop the intake motors
      LeftIntake.stop();
      RightIntake.stop();

      if (trayDone && liftDone && driveDone) {
        // Sequence complete!
        break;
      }
    }

    wait(10, msec); // Play nice with the CPU.
  }

  // Reset all velocities.
  IntakeLift.setVelocity(100, percent);
  LeftIntake.setVelocity(100, percent);
  RightIntake.setVelocity(100, percent);
  TrayPusher.setVelocity(100, percent);

  deployingCubes = false;
}