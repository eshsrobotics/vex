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
void calibrateClaw(vex::motor& clawMotor);

// when the button is pressed the code thats moves the arm and claw keeps
// repeating the same code until the claw reaches its fully open state. it then
// does the reverse when the same button is pressed
void moveArm(double armSpeedPercent,
             ClawState clawState,
             vex::motor& armMotor,
             vex::motor& clawMotor);

// Causes arm motor to move at the given speed instantaneously.
void moveArmInstantaneously(double armSpeedPercent,
                            vex::motor& armMotor);

// Causes claw motor to Keep opening until fully open or keep closing until
// fully closed.
void moveClawContinuously(int clawState,
                            vex::motor& clawMotor);

#endif // (#ifndef ARMSUBSYSTEM_H_IS_PRESENT)