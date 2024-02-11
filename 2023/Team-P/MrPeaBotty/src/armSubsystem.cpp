#include "armSubsystem.h"
#include "hardwareConstitution.h"

using namespace vex;

// As long as the claw angle is changing in the correct direction (positive for
// opening and negative for closing), then this variable controls how big that
// change to convince us where we are closing or opening.
//
// This number was determined arbitrarily determined for programming purposes.
// It still needs to be determined EXPERIMENTALLY.
// WARNING: If this value is too large, closing/opening will get false positives
// as it will get fooled that is done.
const double CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES = 1.0;

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
                Controller.Screen.print(fmt, "CLOSING");
            } else if (clawPosition == CLAW_OPEN) {
                state = OPENING;
                Controller.Screen.print(fmt, "OPENING");
            }
            break;

        case OPENING:
            clawMotor.spin(directionType::fwd, CLAW_SPEED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_CLOSE) {
                state = CLOSING;
                Controller.Screen.print(fmt, "CLOSING");
            } else if (isOpening && fabs(delta) < CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES) {
                state = OPENING_SUSTAINED;
                Controller.Screen.print(fmt, "OPENING_SUSTAINED");
            }
            break;

        case OPENING_SUSTAINED:
            clawMotor.spin(directionType::fwd, CLAW_SPEED_SUSTAINED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_CLOSE) {
                state = CLOSING;
                Controller.Screen.print(fmt, "CLOSING");
            }
            break;

        case CLOSING:
            clawMotor.spin(directionType::fwd, -CLAW_SPEED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (isClosing && fabs(delta) < CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES) {
                state = CLOSING_SUSTAINED;
                Controller.Screen.print(fmt, "CLOSING_SUSTAINED");
            }
            break;

        case CLOSING_SUSTAINED:
            clawMotor.spin(directionType::fwd, -CLAW_SPEED_SUSTAINED_PCT, percentUnits::pct);
            if (clawPosition == CLAW_NEUTRAL) {
                state = DEFAULT_STATE;
                Controller.Screen.print(fmt, "DEFAULT_STATE");
            } else if (clawPosition == CLAW_OPEN) {
                state = OPENING;
                Controller.Screen.print(fmt, "OPENING");
            }
            break;
    };

    lastClawAngleDegrees = clawMotor.position(rotationUnits::deg);
}