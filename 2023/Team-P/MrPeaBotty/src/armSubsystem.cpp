#include "armSubsystem.h"
#include "hardwareConstitution.h"

using namespace vex;

// Will be overwritten by calibrateClaw().
double clawAngleWhenClosedDegrees = 0;

void calibrateClaw(motor& clawMotor, bumper& clawBumper) {

    // Deliberately close claw until we get a read from the claw bump sensor.
    // That tells us the claw has closed.
    clawMotor.spin(fwd, 66, pct);
    while (!clawBumper.pressing()) {
        wait(20, msec);
    }

    // By knowing the angle the claw makes when it is closed, we can easily open
    // to some offset FROM that angle, or return TO that angle in order to
    // re-close the claw.
    //
    // Now is tha time.  Get the angle.
    clawAngleWhenClosedDegrees = clawMotor.position(deg);
}

void moveArm(double armSpeedPercent,
             ClawState clawState,
             motor& armMotorLeft,
             motor& armMotorRight,
             motor& clawMotor) {

    if (armSpeedPercent != 0) {
        armMotorLeft.spin(directionType::fwd, armSpeedPercent, percentUnits::pct);
        armMotorRight.spin(directionType::fwd, -armSpeedPercent, percentUnits::pct);
    } else {
        armMotorLeft.stop(ARM_BRAKE_TYPE);
        armMotorRight.stop(ARM_BRAKE_TYPE);
    }

    // open or close the claw and keep going till it is done. Zero degrees is
    // considered fully open, and 90 degrees is considered fully closed (for now).
    const double CLAW_VELOCITY_PCT = 80;
    const double CLAW_ANGLE_WHEN_OPEN_DEGREES = 90 + clawAngleWhenClosedDegrees;

    // What is the claw's current angle?  0 is fully closed, 90 is open to the
    // trap-jaw angle.
    const double CURRENT_CLAW_ANGLE_DEGREES = clawMotor.position(deg) + clawAngleWhenClosedDegrees;

    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("Claw Angle: %.1f  ", CURRENT_CLAW_ANGLE_DEGREES);

    switch (clawState) {
        case CLAW_NEUTRAL:
            // If the claw's open, leave it open.  If the claw is biting, let it
            // bite.
            return;
        case CLAW_OPEN:
            if (CURRENT_CLAW_ANGLE_DEGREES >= 90) {
                // The claw is already fully open.  Opening it more would just
                // break the bot.
                return;
            }
            clawMotor.spinToPosition(CLAW_ANGLE_WHEN_OPEN_DEGREES,
                                     deg,
                                     CLAW_VELOCITY_PCT,
                                     vex::velocityUnits::pct,
                                     false);
            break;

        case CLAW_CLOSE:
            if(CURRENT_CLAW_ANGLE_DEGREES <= 0) {
                // Like the CLA_OPEN function, if we try to close the claw even
                // more, then it would break the bot.
                return;
            }
            // We're setting the clawMotor to spin to 0 degrees regardless if
            // there's something interrupting, so that the claw can keep biting
            // down on the triball.
            clawMotor.spinToPosition(clawAngleWhenClosedDegrees,
                                     deg,
                                     CLAW_VELOCITY_PCT,
                                     vex::velocityUnits::pct,
                                     false);
            break;
    };


    //clawMotor.setTimeout(1000 * CLAW_OPEN_TIMEOUT_SEC, timeUnits::msec);
}
