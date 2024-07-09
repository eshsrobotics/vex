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

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
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


    vex::wait(50, msec);
  }
}
