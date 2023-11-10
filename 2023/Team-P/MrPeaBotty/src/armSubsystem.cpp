#include "armSubsystem.h"

using namespace vex;

void moveArm(double armSpeedPercent,
             bool clawClose,
             motor& armMotor,
             motor& clawMotor) {

    armMotor.spin(directionType::fwd, armSpeedPercent, percentUnits::pct);

    // open or close the claw and keep going till it is done
    const double CLAW_OPEN_DEGREES = 90;
    const double CLAW_OPEN_TIMEOUT_SEC = 0.5;
    const double CLAW_VELOCITY_PCT = 80;
    const bool BLOCK_UNTIL_DONE = true;

    clawMotor.setTimeout(1000 * CLAW_OPEN_TIMEOUT_SEC, timeUnits::msec);
    clawMotor.setVelocity(CLAW_VELOCITY_PCT, percentUnits::pct);
    clawMotor.spinFor(directionType::fwd, 
                      CLAW_OPEN_DEGREES, 
                      rotationUnits::deg, 
                      BLOCK_UNTIL_DONE);
}