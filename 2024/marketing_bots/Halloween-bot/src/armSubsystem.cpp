#include "armSubsystem.h"
#include "hardwareConstitution.h"

using namespace vex;

// Will be overwritten by calibrateClaw().
const double INVALID_CLAW_ANGLE = -1234.0;
double clawAngleWhenClosedDegrees = INVALID_CLAW_ANGLE;

void calibrateClaw(motor& clawMotor, bumper& clawBumper) {

    if (clawAngleWhenClosedDegrees != INVALID_CLAW_ANGLE) {
        // We are already calibrated!  No-op.
        return;
    }

    // Deliberately close claw until we get a read from the claw bump sensor.
    // That tells us the claw has closed.
    clawMotor.spin(fwd, CLAW_CALIBRATION_CLOSURE_SPEED_PCT, pct);
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
    const double CLAW_ANGLE_WHEN_OPEN_DEGREES = clawAngleWhenClosedDegrees - 90;

    // What is the claw's current angle?  0 is fully closed, 90 is open to the
    // trap-jaw angle.
    const double CURRENT_CLAW_ANGLE_DEGREES = clawAngleWhenClosedDegrees - clawMotor.position(deg);

    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("Claw %6s at %.1f°", 
                            getBumper().pressing() ? "Closed" : "Open",
                            CURRENT_CLAW_ANGLE_DEGREES);

    switch (clawState) {
        case CLAW_NEUTRAL:
            // If the claw's open, leave it open.  If the claw is biting, let it
            // bite.
            clawMotor.stop(brakeType::brake);
            break;
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
            if(CURRENT_CLAW_ANGLE_DEGREES <= -CLAW_OVERBITE_ANGLE_DEGREES) {
                // Like the CLAW_OPEN function, if we try to close the claw even
                // more, then it would break the bot.
                return;
            }
            // We're setting the clawMotor to spin to 0 degrees regardless if
            // there's something interrupting, so that the claw can keep biting
            // down on the triball.
            clawMotor.spinToPosition(clawAngleWhenClosedDegrees - CLAW_OVERBITE_ANGLE_DEGREES,
                                     deg,
                                     CLAW_VELOCITY_PCT,
                                     vex::velocityUnits::pct,
                                     false);
            break;
    };


    //clawMotor.setTimeout(1000 * CLAW_OPEN_TIMEOUT_SEC, timeUnits::msec);
}
