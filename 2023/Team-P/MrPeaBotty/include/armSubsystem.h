#ifndef ARMSUBSYSTEM_H_IS_PRESENT
#define ARMSUBSYSTEM_H_IS_PRESENT

#include "vex.h"

enum ClawState {
    CLAW_OPEN,
    CLAW_CLOSE,
    CLAW_NEUTRAL
};

// When the robot starts, we don't know if the claw is open or closed.  That's a
// problem, because we need to know how many degrees to move the arm in order to
// open or close it. Also, if the arm _is_ open, we don't want t open it any
// further.
//
// To get the initial state of the claw, this function forcibly closes it until
// a bump sensor activates.  At that point, we know that the claw is closed, and
// we make a record of its current encoder position.  The open position is
// always relative to that.
void calibrateClaw(vex::motor& clawMotor,
                   vex::bumper& clawBumper);

// when the button is pressed the code thats moves the arm and claw keeps
// repeating the same code until the claw reaches its fully open state. it then
// does the reverse when the same button is pressed
void moveArm(double armSpeedPercent,
             ClawState clawState,
             vex::motor& armMotorLeft,
             vex::motor& armMotorRight,
             vex::motor& clawMotor);

// We decided to go with brake, because, if we use coast, then, if we're
// possessing a triball and we're going up, and we use coast, then the triball
// might weigh us down, causing the arm to go down.
//
// Hold will require constant energy usage in order to make the arm stay up.
const vex::brakeType ARM_BRAKE_TYPE = vex::brakeType::brake;

#endif // (#ifndef ARMSUBSYSTEM_H_IS_PRESENT)
