#ifndef ARMSUBSYSTEM_H_IS_PRESENT
#define ARMSUBSYSTEM_H_IS_PRESENT

#include "vex.h"

enum ClawState {
    CLAW_OPEN,
    CLAW_CLOSE,
    CLAW_NEUTRAL
};

// How quickly the claw closes during the initial calibration.
const double CLAW_CALIBRATION_CLOSURE_SPEED_PCT = 25.0;

// When the robot starts, we don't know if the claw is open or closed.  That's a
// problem, because we need to know how many degrees to move the arm in order to
// open or close it. Also, if the arm _is_ open, we don't want t open it any
// further.
//
// To get the initial state of the claw, this function forcibly closes it until
// a bump sensor activates.  At that point, we know that the claw is closed, and
// we make a record of its current encoder position.  The open position is
// always relative to that.
//
// Note: We deliberately make calibrateClaw() idempotent, meaning that running
// it more than once has no additional effect.  This is because motors are not
// allowed to run during pre_auton(), and calibrateClaw() necessarily runs the
// clawMotor; therefore we have no choice but to call it at the beginning of
// both teleop AND autonomous.
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
//This controls the claw speed during teleop, different from the value used in
//the claw motor spin function. That value affects the claw movement speed during
//calibration.
const double CLAW_VELOCITY_PCT = 20;
// We decided to go with brake, because, if we use coast, then, if we're
// possessing a triball and we're going up, and we use coast, then the triball
// might weigh us down, causing the arm to go down.
//
// Hold will require constant energy usage in order to make the arm stay up.
//We used break at first but realized that it just makes the motor shut down,
//and the part can still be moved, similar to putting a car in neutral.
//Switching to hold.
const vex::brakeType ARM_BRAKE_TYPE = vex::brakeType::hold;

//This constant is here to make the claw close beyond 0 degrees
//in an attempt to increase the bite force of the bot. We're
//making it a constant to modify the value easier in the long run. 
const int CLAW_OVERBITE_ANGLE_DEGREES = 10;
#endif // (#ifndef ARMSUBSYSTEM_H_IS_PRESENT)
