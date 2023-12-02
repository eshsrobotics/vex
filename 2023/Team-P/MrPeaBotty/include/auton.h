#ifndef AUTON_H_IS_INCLUDED
#define AUTON_H_IS_INCLUDED

#include <vector>

enum AutonAction {
     DRIVE_FWD,
     TURN,
     MOVE_ARM,
     OPEN_CLAW
};

struct AutonStep {
    AutonAction action;

    //Parameter tells how much to do the action by.
    //For example, for drive fwd the parameter would be speed.
    double parameter;

    //This is so that the bot knows how long to drive, how long to rotate, etc.
    double timeoutMS;
};

std::vector<AutonStep> autonPlan = {
    {DRIVE_FWD, 50, 500}
};




#endif //AUTON_H_IS_INCLUDED