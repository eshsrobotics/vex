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

#include "vex.h"
#include "robot-config.h"

using namespace vex;

competition Competition;

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
    if (elapsed_time_msec > experiment_duration_ms) {
        Drivetrain.stop();
        intake_roller_motor.stop();
    }
  }
}

/** 
  * The user control section. The code that runs when the driver is in control
  * for remaining 1:45 minutes of the competition.
*/
void teleop() {
  
  
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
