#ifndef AUTON_H_IS_INCLUDED
#define AUTON_H_IS_INCLUDED

#include <vector>

enum AutonAction {
    // Drives forward or backward. The parameter represents the velocity
    // between -100 and 100. 0 stops driving.
    DRIVE_FWD,

    // Turns the chassis. The parameter represents turn speed: +100 is maximum
    // rotation speed clockwise, and -100 is maximum speed counterclockwise. 0
    // stops rotation.
    TURN_CLOCKWISE,

    // Moves the arm. The parameter represents arm movement speed: +100 is
    // maximum arm speed upwards, while -100 is maximum arm speed downwards,
    // and 0 is 0 arm speed.
    MOVE_ARM,

    // Open or closes the claw. A positive parameter opens the claw, while a
    // negative one closes the claw, and 0 stops the claw.
    OPEN_CLAW,
};

struct AutonStep {
    AutonAction action;

    // Parameter tells how much to do the action by.
    // For example, for drive fwd the parameter would be speed.
    double parameter;

    // This is for how soon to start this action after auton begins. Negative
    // values are not allowed.
    double startTimeMS;
};

extern std::vector<AutonStep> autonPlan;

// Takes an auton plan and executes it. Warning: The Last Step in the Plan must
// be a stop action, and will be executed for 1 frame.
void executeAutonPlan(std::vector<AutonStep>& autonPlan);

#endif // AUTON_H_IS_INCLUDED