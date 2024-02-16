#include "armSubsystem.h"
#include "hardwareConstitution.h"

using namespace vex;

// Represents the different things that the claw is doing (it is either doing nothing, closing, etc.)
enum ClawState {

    // Initial state
    START,

    // A state where the claw is neither being opened nor close.
    // - transitions:
    //   * ClawPosition == Claw_Neutral: DEFAULT_STATE
    //   * ClawPosition == Claw_Closed: CLOSING
    //   * ClawPosition == Claw_OPEN: OPENING
    DEFAULT_STATE,

    // A state where the claw is opening but has not completely opened.
    // - transitions:
    //   * ClawPosition == Claw_Closed: CLOSING
    //   * ClawPosition == Claw_Neutral: DEFAULT_STATE
    //   * Angle is opening sufficiently: OPENING
    //   * Angle is not changing much: OPENING_SUSTAINED
    OPENING,

    // A state where the claw has fully opened and wants to remain opened.
    // - transitions:
    //   * ClawPosition == Claw_Neutral: DEFAULT_STATE
    //   * ClawPosition == Claw_Closed: CLOSING
    //   * ClawPosition == Claw_Open: OPENING_SUSTAINED
    OPENING_SUSTAINED,

    // A state where the claw is closing has not completely closed.
    // - transitions:
    //   * ClawPosition == Claw_Open: OPENING
    //   * ClawPosition == Claw_Neutral: DEFAULT_STATE
    //   * Angle is closing sufficiently: CLOSING
    //   * Angle is not closing sufficiently: CLOSING_SUSTAINED
    CLOSING,

    // A state where the claw has fully closed and wants to remain closed.
    // - transitions:
    //   * ClawPosition == claw_Neutral: DEFAULT_STATE
    //   * ClawPosition == claw_Closed: CLOSING_SUSTAINED
    //   * ClawPosition == claw_Open: OPENING
    CLOSING_SUSTAINED
};

void moveArm(double armSpeedPercent,
             ClawPosition clawPosition,
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

    /////////////////////////////////////////////////////////////////////////
    // Move the claw.                                                      //
    //                                                                     //
    // There are a lot of static variables here!  We'll explain them as we //
    // go.                                                                 //
    /////////////////////////////////////////////////////////////////////////

    static ClawState state = START;

    // The angle the clawMotor had at the end of the most recent call to
    // moveArm().  We use this to tell how much how claw has opened or closed;
    // this in turn tells us if we need to stop opening or stop closing.
    static double lastClawAngleDegrees = 0;

    // The time when we started the OPENING or CLOSING states. This matters
    // because we need to close or open for a minimum period of time before
    // going into the SUSTAIN speed.
    //
    // Without this, a delta of 0 will cause us to immediately transition from
    // OPENING to OPENING_SUSTAINED (or CLOSING to CLOSING_SUSTAINED) without
    // the claw actually having been given a chance to move.
    static double startTimeMilliseconds = 0;

    // During the CLAW_OPEN and/or CLAW_CLOSE states, we open or close the
    // claw, changing its angle until we perceive that the change has stopped
    // somehow (due to being fully open or fully closed -- this is how we
    // avoid needing additional sensors.)  But our previous strategy of just
    // continuing to run the claw motor after that led to the motor going
    // limp after a few cycles of opening and closing!  We suspect, but have
    // no proof, that we somehow tripped a built-in VEX smart motor failsafe
    // in so doing.
    //
    // So how do we maintain the fully-open or fully-closed position properly?
    // Easy: ask the motor to do that itself.  By saving the claw angle when
    // we detect that opening or closing has stopped, we can call
    // clawMotor.setPosition() to make the motor's built-in firmware maintain
    // a holding pattern at that position.
    //
    // It's like having a servo with more steps.
    static double recordedClawAngleDegrees = 0;

    // Change in angle since the last time moveArm() was called.
    double delta = clawMotor.position(rotationUnits::deg) - lastClawAngleDegrees;

    // In the following code, we are assuming that negative numbers for the
    // clawMotor.spin closes the claw and positive numbers open it.
    bool isOpening = (delta >= 0);
    bool isClosing = (delta <= 0);

    Controller.Screen.setCursor(1, 1);
    const char* fmt = "%-17s";
    switch (state) {
        case START:
            state = DEFAULT_STATE;
            Controller.Screen.print(fmt, "DEFAULT_STATE");
            break;

        case DEFAULT_STATE:
            clawMotor.stop(brakeType::hold);
            if (clawPosition == CLAW_CLOSE) {
                state                    = CLOSING;
                recordedClawAngleDegrees = clawMotor.position(rotationUnits::deg);
                startTimeMilliseconds    = Brain.timer(msec);
                Controller.Screen.print(fmt, "CLOSING");
            } else if (clawPosition == CLAW_OPEN) {
                state                    = OPENING;
                recordedClawAngleDegrees = clawMotor.position(rotationUnits::deg);
                startTimeMilliseconds    = Brain.timer(msec);
                Controller.Screen.print(fmt, "OPENING");
            }
            break;

        case OPENING:
            clawMotor.spin(directionType::rev, CLAW_SPEED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_CLOSE) {
                state                    = CLOSING;
                recordedClawAngleDegrees = clawMotor.position(rotationUnits::deg);
                startTimeMilliseconds    = Brain.timer(msec);
                Controller.Screen.print(fmt, "CLOSING");
            } else if (isOpening &&
                       fabs(delta) < CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES &&
                       Brain.timer(msec) - startTimeMilliseconds > MINIMUM_TIME_BEFORE_SUSTAIN_MILLISECONDS) {
                // We've opened long enough, and the angle isn't changing.  Go
                // into a holding pattern!
                state = OPENING_SUSTAINED;
                Controller.Screen.print(fmt, "OPENING_SUSTAINED");
            }
            break;

        case OPENING_SUSTAINED:
            clawMotor.setPosition(recordedClawAngleDegrees, rotationUnits::deg);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_CLOSE) {
                state = CLOSING;
                startTimeMilliseconds = Brain.timer(msec);
                Controller.Screen.print(fmt, "CLOSING");
            }
            break;

        case CLOSING:
            clawMotor.spin(directionType::fwd, CLAW_SPEED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (isClosing &&
                       fabs(delta) < CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES &&
                       Brain.timer(msec) - startTimeMilliseconds > MINIMUM_TIME_BEFORE_SUSTAIN_MILLISECONDS) {
                // We've closed long enough, and the angle isn't changing.  Go
                // into a holding pattern!
                state = CLOSING_SUSTAINED;
                Controller.Screen.print(fmt, "CLOSING_SUSTAINED");
            }
            break;

        case CLOSING_SUSTAINED:
            clawMotor.setPosition(recordedClawAngleDegrees, rotationUnits::deg);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_OPEN) {
                state                    = OPENING;
                recordedClawAngleDegrees = clawMotor.position(rotationUnits::deg);
                startTimeMilliseconds    = Brain.timer(msec);
                Controller.Screen.print(fmt, "OPENING");
            }
            break;
    };

    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("Pos: %-12s",
        (clawPosition == CLAW_NEUTRAL ? "CLAW_NEUTRAL" :
            (clawPosition == CLAW_OPEN ? "CLAW_OPEN" : "CLAW_CLOSE")));
    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("Power: %.2fW  ", clawMotor.power(watt));

    lastClawAngleDegrees = clawMotor.position(rotationUnits::deg);
}
