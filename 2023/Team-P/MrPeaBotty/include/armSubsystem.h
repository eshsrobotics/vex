#ifndef ARMSUBSYSTEM_H_IS_PRESENT
#define ARMSUBSYSTEM_H_IS_PRESENT

#include "vex.h"

// Makes the claw move in the way that the caller of the function moveArm wants.
enum ClawPosition {
    CLAW_OPEN,
    CLAW_CLOSE,
    CLAW_NEUTRAL
};

// How quickly the claw closes/opens in the CLOSING and OPENING states.
const double CLAW_SPEED_PCT = 70;

// As long as the claw angle is changing in the correct direction (positive
// for opening and negative for closing), then this variable controls how big
// that change to convince us that we are still closing or opening.
//
// WARNING: If this value is too large, closing/opening will get false
// positives as it will get fooled into 'thinking' that is done.
const double CLAW_ANGLE_CHANGE_THRESHOLD_DEGREES = 0.05;

// The claw must open or close for at least this long before we are willing to
// consider stopping it.  This prevents us from thinking the claw is "open"
// when it's really still closed, and vice versa.
//
// Don't make this value 0 for that reason.  Also, avoid making it too long so
// that the motor doesn't strain.  More than 500 milliseconds is probably
// excessive.
const double MINIMUM_TIME_BEFORE_SUSTAIN_MILLISECONDS = 500;

// when the button is pressed the code thats moves the arm and claw keeps
// repeating the same code until the claw reaches its fully open state. it then
// does the reverse when the same button is pressed
void moveArm(double armSpeedPercent,
             ClawPosition clawPosition,
             vex::motor& armMotorLeft,
             vex::motor& armMotorRight,
             vex::motor& clawMotor);

// We decided to go with brake, because, if we use coast, then, if we're
// possessing a triball and we're going up, and we use coast, then the triball
// might weigh us down, causing the arm to go down.
//
// Hold will require constant energy usage in order to make the arm stay up.
//We used break at first but realized that it just makes the motor shut down,
//and the part can still be moved, similar to putting a car in neutral.
//Switching to hold.
const vex::brakeType ARM_BRAKE_TYPE = vex::brakeType::hold;

#endif // (#ifndef ARMSUBSYSTEM_H_IS_PRESENT)
