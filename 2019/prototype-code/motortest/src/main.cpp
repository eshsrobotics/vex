// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontRightWheel      motor         1
// FrontLeftWheel       motor         9
// BackRightWheel       motor         3
// BackLeftWheel        motor         4
// LeftIntake           motor         13
// RightIntake          motor         7
// IntakeLift           motor         10
// TrayPusher           motor         8
// Controller1          controller
// PotentiometerA       pot           A
// RED_AUTON_LED        led           B
// BLUE_AUTON_LED       led           C
// ---- END VEXCODE CONFIGURED DEVICES ----

///////////////////////////////////////////////
// ports 2, 5, and 6  DO NOT WORK !!!!!!!!!!! //
///////////////////////////////////////////////

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
#include "autonomous.h"

void deployCubes();

const double SNEAK_PERCENTAGE = 0.50;
const double INTAKE_LIFT_VELOCITY = 85; // Out of 100
const double TRAY_PUSH_VELOCITY = 13;

AutonomousSelection autonomous_selection;
bool sneak = false;
bool deployingCubes = false;

void mecanumDrive(int leftRight, int forwardBack, int turn) {
  // If sneak is enabled, reduce speed.
  double multiplier = 1.0;
  if (sneak) {
    multiplier = SNEAK_PERCENTAGE;
  }

  FrontRightWheel.spin(forward, multiplier * (forwardBack - turn + leftRight),
                       percent);
  BackRightWheel.spin(forward, multiplier * (forwardBack - turn - leftRight),
                      percent);
  FrontLeftWheel.spin(forward, multiplier * (forwardBack + turn + leftRight),
                      percent);
  BackLeftWheel.spin(forward, multiplier * (forwardBack + turn - leftRight),
                     percent);
}

// Switches the autonomous selection from RED to BLUE based on the potentiometer value.
// We also take care of firing the respective LEDs.
//
// This code is meant to be called as part of the changed() function for the
// selection potentiometer.
void update_autonomous_selection() {

  // Are we going with the red sequence of autonomous operations, or
  // the blue sequence?
  //
  // The VEX potentiometer has a range of 250 ± 20º, giving an effective
  // range of 230º.
  const double MIN_ANGLE_DEGREES = 0.0;
  const double MAX_ANGLE_DEGREES = 250.0;
  double angle = PotentiometerA.angle(degrees);
  double range = MAX_ANGLE_DEGREES - MIN_ANGLE_DEGREES;
  if (angle > 0.50 * range) {
    autonomous_selection = BLUE;
    RED_AUTON_LED.off();
    BLUE_AUTON_LED.on();
  } else {
    autonomous_selection = RED;
    BLUE_AUTON_LED.off();
    RED_AUTON_LED.on();
  }
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 3);
  Controller1.Screen.print("Pot = %.2f", angle);
  Controller1.Screen.setCursor(2, 3);
  Controller1.Screen.print("Sel = %d", autonomous_selection);
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

  // Register a handler to be fired whenever the potentiometer changes (and
  // not just during pre-auton().)
  PotentiometerA.changed(update_autonomous_selection);

  // Read the potentiometer value at program start.
  // Calling changed() will only read the potentiometer when it is turned by hand!
  update_autonomous_selection();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // Enough with the slow motors out of the box already!
  IntakeLift.setVelocity(INTAKE_LIFT_VELOCITY, percent);
  TrayPusher.setVelocity(TRAY_PUSH_VELOCITY, percent);
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
  execute(blue_operations); 
  
  // update_autonomous_selection();
  // switch (autonomous_selection) {
  //   case UNDEFINED:
  //     break;
  //   case RED:
  //     execute(red_operations);
  //     break;

  // }
  // if (autonomous_selection == BLUE) {
  //   execute(blue_operations);
  // } else {
  //   // execute(red_operations);
  // }
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
  update_autonomous_selection();
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
    if (!deployingCubes) {
      mecanumDrive(leftRight, forwardBack, turn);
    }

    // Sets the position of the intake lift using increments of 5 degrees
    //
    // We know the proper way to move the motor via encoders:
    // IntakeLift.spinToPosition().
    //
    // But it is not easy to detemrine when that function should be called.
    if (Controller1.ButtonR2.pressing()) {
      IntakeLift.spin(forward);
    } else if (Controller1.ButtonR1.pressing()) {
      IntakeLift.spin(reverse);
    } else if (!deployingCubes) {
      bool waitForCompletion = false;
      IntakeLift.spinToPosition(IntakeLift.position(degrees), degrees,
                                waitForCompletion);
    }

    // Controller1.ButtonA.pressed([] () {
    //   if (!deployingCubes) {
    //     deployCubes();
    //   }
    // });

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }                 // end (loop forever)
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
  // (2) Right before the tray is fully pushed, lift the intake and start
  // reversing the intake motors (3) Stop the intake lift and back off while the
  // intake motors are still hot (4) Stop the intake motors and return the tray
  // and lift to start position
  const double TRAY_PUSH_START_SECONDS = 0.0;
  const double TRAY_PUSH_DURATION_SECONDS = 3.5;
  const double TRAY_SPEED_PERCENT = 15.0;

  const double INTAKE_LIFT_START_SECONDS = 0.5;
  const double INTAKE_LIFT_DURATION_SECONDS = 3.0;
  const double INTAKE_LIFT_SPEED_PERCENT = 50.0;

  const double INTAKE_SPEED_PERCENT = 38.0;
  const double INTAKE_ACTIVATION_DELAY = 3.0;

  const double BACKOFF_START_SECONDS = 5.0;
  const double BACKOFF_DURATION_SECONDS = 1.0;
  const double BACKOFF_SPEED_PERCENT = 50.0;

  // Set initial velocities
  IntakeLift.setVelocity(INTAKE_LIFT_SPEED_PERCENT, percent);
  TrayPusher.setVelocity(TRAY_SPEED_PERCENT, percent);
  LeftIntake.setVelocity(INTAKE_SPEED_PERCENT, percent);
  RightIntake.setVelocity(INTAKE_SPEED_PERCENT, percent);

  // We don't want the intakes moving until we say so.
  LeftIntake.stop();
  RightIntake.stop();

  double startTimeMilliseconds = Brain.timer(msec);
  while (true) {

    double elapsedTimeSeconds =
        (Brain.timer(msec) - startTimeMilliseconds) / 1000.0;
    bool trayDone = false, liftDone = false, driveDone = false;

    ///////////////////
    // MOVE THE TRAY //
    ///////////////////

    if (elapsedTimeSeconds > TRAY_PUSH_START_SECONDS &&
        elapsedTimeSeconds <
            TRAY_PUSH_START_SECONDS + TRAY_PUSH_DURATION_SECONDS) {

      // Push the tray out.
      TrayPusher.spin(reverse);

    } else if (elapsedTimeSeconds > BACKOFF_START_SECONDS - 1 &&
               elapsedTimeSeconds <
                   BACKOFF_START_SECONDS - 1 + TRAY_PUSH_DURATION_SECONDS) {

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
        elapsedTimeSeconds <
            INTAKE_LIFT_START_SECONDS + INTAKE_LIFT_DURATION_SECONDS) {

      IntakeLift.spin(forward);

      // Start the intake motors here.
      if (elapsedTimeSeconds >
          INTAKE_LIFT_START_SECONDS + INTAKE_ACTIVATION_DELAY) {
        LeftIntake.spin(reverse);
        RightIntake.spin(forward);
      }

    } else if (elapsedTimeSeconds >
                   BACKOFF_START_SECONDS + BACKOFF_DURATION_SECONDS &&
               elapsedTimeSeconds < BACKOFF_START_SECONDS +
                                        BACKOFF_DURATION_SECONDS +
                                        INTAKE_LIFT_DURATION_SECONDS) {

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
      mecanumDrive(0, 0, -BACKOFF_SPEED_PERCENT);

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
  IntakeLift.setVelocity(INTAKE_LIFT_VELOCITY, percent);
  LeftIntake.setVelocity(100, percent);
  RightIntake.setVelocity(100, percent);
  TrayPusher.setVelocity(TRAY_PUSH_VELOCITY, percent);

  deployingCubes = false;
}
