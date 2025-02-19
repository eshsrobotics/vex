// hardware.cpp: Contains the definitions for the declarations made in hardware.h

#include "hardware.h"
#include <algorithm>

using namespace vex;
using std::max;
using std::min;

brain Brain;
controller Controller;

motor FrontLeft(FRONT_LEFT_PORT, true);
motor FrontRight(FRONT_RIGHT_PORT);
motor BackLeft(BACK_LEFT_PORT, true);
motor BackRight(BACK_RIGHT_PORT);
motor FrontLiftRight(LiftFR);
motor BackLiftLeft(LiftBL);

//Positive velocities close the clamp, while negative velocities open the clamp.
motor Clamp(CLAMP_PORT);

limit ClampLimit(Brain.ThreeWirePort.C);

motor Intake(INTAKE_PORT);

motor_group Left(FrontLeft, BackLeft);
motor_group Right(FrontRight, BackRight);
drivetrain DriveTrain(Left, Right, WHEEL_CIRCUMFERENCE_CM, 
                      DRIVE_TRAIN_WIDTH_CM, DRIVE_TRAIN_LENGTH_CM, 
                      distanceUnits::cm, DRIVE_TRAIN_GEAR_RATIO);

motor_group updownlift(FrontLiftRight, BackLiftLeft);

/**
 * We are using a state machine, meaning that we're constantly switching between
 * different "states" where various different actions are done. The enum class
 * below represents the different states of the state machine as enum values. 
 */
enum class ClampState {
    Start,
    Opening,
    Closing,
    FullyOpen,
    FullyClosed,
};

void robotDrive(double frontBackSpeed, double turnSpeed) {

    // This is set to false because it seems that only one drive method is allowed 
    // at a time, so turn() would cancel out drive().
    const bool vexDoesTheRightThing = false;
    
    if (vexDoesTheRightThing) {
        // Option 1: Drive Train internally Does the Right Thing™ and combines
        // turning and forward/back speed to produce an overall chassis speed.
        //
        // This would be ideal!  But we're not sure if this is what VEX V5 does.
        DriveTrain.drive(fwd, frontBackSpeed, velocityUnits::pct);
        DriveTrain.turn(vex::turnType::right, turnSpeed, velocityUnits::pct);
    } else {
        // Option 2: The above does not apply.  That is, telling the DriveTrain
        // to turn() causes forward/back movement to be canceled and vice versa.
        // In that case, we power the drive ourselves.
        //
        // This is EXACTLY the arcade drive use case!
        double leftMotorSpeed = (frontBackSpeed + turnSpeed);
        double rightMotorSpeed = (frontBackSpeed - turnSpeed);
        leftMotorSpeed = max(-100.0, min(leftMotorSpeed, 100.0));
        rightMotorSpeed = max(-100.0, min(rightMotorSpeed, 100.0));

        Left.spin(fwd, leftMotorSpeed, velocityUnits::pct);
        Right.spin(fwd, rightMotorSpeed, velocityUnits::pct);
    }

}
//When testing if Intake and Outake are reversed change the code for it to be
//reversed.
void robotintake(int intakeOrOuttake) {
    Intake.setVelocity(100.00, vex::percentUnits::pct);
    if (intakeOrOuttake > 0) {
        // Intaking.
        Intake.spin(vex::directionType::fwd);
    } else if (intakeOrOuttake < 0) {
        // Outtaking
        Intake.spin(vex::directionType::rev);
    } else {
        // No movement
        Intake.stop(vex::brakeType::brake);
    }
}

//Lift system code
void robotlift(int lift) {
    updownlift.setVelocity(100.00, vex::percentUnits::pct);
    if (lift > 0) {
        updownlift.spin (vex::directionType::fwd);
    } else if (lift < 0) {
        updownlift.spin(vex::directionType::rev);
    } else {
        updownlift.stop(vex::brakeType::brake);
    }
}

//Clamp code
void updateClampState(bool close) {
    static ClampState clampStatus = ClampState::Start;
    static double startTimeSec = 0;
    Controller.Screen.setCursor(1,1);
    Controller.Screen.print("Limit = %d", ClampLimit.value());
    switch(clampStatus) {
        case ClampState::Start:
            startTimeSec = Brain.timer(vex::timeUnits::sec);
            if (close == true) {           
                clampStatus = ClampState::Closing;
            } else {
                clampStatus = ClampState::Opening;
            }
            break;
        
        case ClampState::Opening:
            Clamp.spin(vex::directionType::rev, CLAMP_VELOCITY_PCT, pct);
            if (Brain.timer(vex::timeUnits::sec) >= OPEN_CLAMP_TIMEOUT_SEC + startTimeSec || ClampLimit.value() > 0) {
                clampStatus = ClampState::FullyOpen;
            } else if (close == true) {
                // User stopped opening and is now closing the clamp.
                startTimeSec = Brain.timer(vex::timeUnits::sec);
                clampStatus = ClampState::Closing;
            }
            break;
        
        case ClampState::Closing:
            Clamp.spin(vex::directionType::fwd, CLAMP_VELOCITY_PCT, pct);
            if (Brain.timer(vex::timeUnits::sec) >= CLOSE_CLAMP_TIMEOUT_SEC + startTimeSec) {
                clampStatus = ClampState::FullyClosed;
            } else if (close == false) { 
                // User stopped closing and is now opening the clamp.
                startTimeSec = Brain.timer(vex::timeUnits::sec);
                clampStatus = ClampState::Opening;
            }
            break;

        case ClampState::FullyOpen:
            Clamp.stop(vex::hold);
            if (close == true) {
                // User is closing the fully open clamp.
                startTimeSec = Brain.timer(vex::timeUnits::sec);
                clampStatus = ClampState::Closing;
            }
            break;

        case ClampState::FullyClosed:
            Clamp.stop(vex::hold);
            if (close == false) {
                // User is opening the fully closed clamp.
                startTimeSec = Brain.timer(vex::timeUnits::sec);
                clampStatus = ClampState::Opening;
            }
            break;


    }
}