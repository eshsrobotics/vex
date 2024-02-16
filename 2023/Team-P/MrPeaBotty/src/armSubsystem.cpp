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

    static ClawState state = START;
    static double lastClawAngleDegrees = 0;

    // The time when we started the OPENING or CLOSING states. This matters
    // because we need to close or open for a minimum period of time before
    // going into the SUSTAIN speed.
    //
    // Without this, a delta of 0 will cause us to immediately transition from
    // OPENING to OPENING_SUSTAINED (or CLOSING to CLOSING_SUSTAINED) without
    // the claw actually having opened or closed.
    static double startTimeMilliseconds = 0;

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
                state = CLOSING;
                startTimeMilliseconds = Brain.timer(msec);
                Controller.Screen.print(fmt, "CLOSING");
            } else if (clawPosition == CLAW_OPEN) {
                state = OPENING;
                startTimeMilliseconds = Brain.timer(msec);
                Controller.Screen.print(fmt, "OPENING");
            }
            break;

        case OPENING:
            clawMotor.spin(directionType::rev, CLAW_SPEED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_CLOSE) {
                state = CLOSING;
                startTimeMilliseconds = Brain.timer(msec);
                Controller.Screen.print(fmt, "CLOSING");
            } else if (isOpening && 
                       //fabs(delta) < CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES && 
                       Brain.timer(msec) - startTimeMilliseconds > MINIMUM_TIME_BEFORE_SUSTAIN_MILLISECONDS) {
                state = OPENING_SUSTAINED;
                Controller.Screen.print(fmt, "OPENING_SUSTAINED");
            }
            break;

        case OPENING_SUSTAINED:
            clawMotor.spin(directionType::rev, CLAW_SPEED_OPENING_SUSTAINED_PCT, percentUnits::pct);
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
                       //fabs(delta) < CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES && 
                       Brain.timer(msec) - startTimeMilliseconds > MINIMUM_TIME_BEFORE_SUSTAIN_MILLISECONDS) {
                state = CLOSING_SUSTAINED;
                Controller.Screen.print(fmt, "CLOSING_SUSTAINED");
            }
            break;

        case CLOSING_SUSTAINED:
            clawMotor.spin(directionType::fwd, CLAW_SPEED_CLOSING_SUSTAINED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_OPEN) {
                state = OPENING;
                startTimeMilliseconds = Brain.timer(msec);
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