#ifndef ARMSUBSYSTEM_H_IS_PRESENT
#define ARMSUBSYSTEM_H_IS_PRESENT

#include "vex.h"

// when the button is pressed the code thats moves the arm and claw keeps
// repeating the same code until the claw reaches its fully open state. it then
// does the reverse when the same button is pressed
void moveArm(double armSpeedPercent,
             bool clawClose,
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