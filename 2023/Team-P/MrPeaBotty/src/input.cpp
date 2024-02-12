#include "input.h"
#include "hardwareConstitution.h"
#include <algorithm>

using std::abs;
using std::max;
using namespace vex;

void tank_drive(double leftSpeedPercent,
                double rightSpeedPercent,
                motor_group& left,
                motor_group& right) {

    // Deadzones are the region where the input is so low it's registered as zero input.
    // Since controllers aren't precise, and don't return to "position 0" when you take
    // your finger off, we need a deadzone value where we cut output when the input is too low.

    if (leftSpeedPercent > JOYSTICK_DEADZONE_PERCENT || leftSpeedPercent < -JOYSTICK_DEADZONE_PERCENT) {
        left.spin(directionType::fwd, leftSpeedPercent, percentUnits::pct);
    } else {
        left.stop(DRIVE_BRAKE_TYPE); //This is to make sure that when the input hits the deadzone, the bot stops moving.
    }
    if (rightSpeedPercent > JOYSTICK_DEADZONE_PERCENT || rightSpeedPercent < -JOYSTICK_DEADZONE_PERCENT) {
        right.spin(directionType::fwd, rightSpeedPercent, percentUnits::pct);
    } else {
        right.stop(DRIVE_BRAKE_TYPE);
    }
}


void arcade_drive(double horizontalChannel,
                  double verticalChannel,
                  vex::motor_group& left,
                  vex::motor_group& right) {

    double straightSpeed = verticalChannel;
    double spinSpeed = horizontalChannel;

    // Dead zones are where the joystick value sets to zero within a certain
    // radius of the center.
    if (fabs(straightSpeed)< JOYSTICK_DEADZONE_PERCENT) {
        straightSpeed = 0;
    }
    if (fabs(spinSpeed)< JOYSTICK_DEADZONE_PERCENT) {
        spinSpeed = 0;
    }

    if (spinSpeed == 0 && straightSpeed == 0) {
        // This stops the robot if the user lets go of the joystick.
        left.stop(DRIVE_BRAKE_TYPE);
        right.stop(DRIVE_BRAKE_TYPE);
    } else {
        // This makes the robot move forward if the user moves the joystick.
        double leftSpeed = -(straightSpeed + spinSpeed);
        double rightSpeed = -(straightSpeed - spinSpeed) * -1.0;

        left.spin(forward, leftSpeed, percent);
        right.spin(forward, rightSpeed, percent);
    }
}

// Use an algorithm that determines the arcade drive motor strengths
// by calculating the quadrant of the velocity vector.
//
// Note that this function studiously avoids using the vex::motorgroup object.
void arcade_drive_by_quadrant(double rotate, double drive) {


    double maximum = max(abs(drive), abs(rotate));
    double total = drive + rotate, difference = drive - rotate;

    auto spinLeftMotors = [](double speedPct) {
        L1.spin(fwd, speedPct, pct);
        L2.spin(fwd, speedPct, pct);
    };

    auto spinRightMotors = [](double speedPct) {
        R1.spin(fwd, speedPct, pct);
        R2.spin(fwd, speedPct, pct);
    };

    if (drive == 0 && rotate == 0) {
        L1.stop(DRIVE_BRAKE_TYPE);
        L2.stop(DRIVE_BRAKE_TYPE);
        R1.stop(DRIVE_BRAKE_TYPE);
        R2.stop(DRIVE_BRAKE_TYPE);
    }

    if (drive >= 0) {
        if (rotate >= 0) {
            // Quadrant 1.
            spinLeftMotors(maximum);
            spinRightMotors(difference);
        } else {
            // Quadrant 2.
            spinLeftMotors(total);
            spinRightMotors(maximum);
        }
    } else {
        if (rotate >= 0) {
            // Quadrant 4.
            spinLeftMotors(total);
            spinRightMotors(-maximum);
        } else {
            // Quadrant 3.
            spinLeftMotors(-maximum);
            spinRightMotors(difference);
        }
    }
}

ControlMapping getControlMapping(DriveScheme driveScheme) {

    ControlMapping mapping;

    switch (driveScheme) {

        // Drive scheme proposed by Leo on 2024-02-11.  Allows all of the
        // useful controls (except the claw) to be on one side of the
        // controller.
        case LEO_DRIVE_SCHEME:
            mapping.arcade_drive_enabled = false;
            mapping.leftSpeed            = Controller.Axis3.position();
            mapping.rightSpeed           = Controller.Axis2.position();

            mapping.armPower             = 0;
            if (Controller.ButtonUp.pressing()) {
                mapping.armPower         = 100;
            } else if (Controller.ButtonDown.pressing()) {
                mapping.armPower         = -100;
            }

            if (Controller.ButtonL1.pressing()) {
                mapping.clawPosition     = CLAW_OPEN;
            } else if (Controller.ButtonL2.pressing()) {
                mapping.clawPosition     = CLAW_CLOSE;
            }
            break;

        // Our initial drive scheme.
        case DEFAULT_DRIVE_SCHEME:
        default:
            mapping.arcade_drive_enabled = true;
            mapping.turnLeftRight        = Controller.Axis4.position();
            mapping.driveForwardBack     = Controller.Axis3.position();
            mapping.armPower             = -Controller.Axis2.position();
            mapping.clawPosition         = CLAW_NEUTRAL;
            if (Controller.ButtonL1.pressing()) {
                mapping.clawPosition     = CLAW_OPEN;
            } else if (Controller.ButtonR1.pressing()) {
                mapping.clawPosition     = CLAW_CLOSE;
            }
            break;
    }

    return mapping;
}
