// This file will contain lift stuff that is not a derived class of Ilift.

#include "Ilift.h"
#include "vex.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * Contains the values for the state machine in the updateLiftState function.
 *
 * The state transition conditions are documented in an image and a graphviz
 * .DOT document: ../docs/lift-state-machine.png
 */
enum class LiftState {
    START,
    DEFAULT_UP,
    MOBILE_GOAL,
    MOBILE_GOAL_DOWN,
    MOBILE_GOAL_UP,
    ALLIANCE_STAKE,
    ALLIANCE_STAKE_UP,
    ALLIANCE_STAKE_DOWN,
    WALL_STAKE,
    WALL_STAKE_DOWN,
};

LiftState INITIAL_LIFT_STATE = LiftState::START;

void updateLiftState(bool upButton, bool downButton,
                     Ilift& robotWithLift, LiftState& state) {

}


// void updateLiftState(bool lowestHeight,
//                      bool mobileGoalLift,
//                      bool allianceStakeLift,
//                      bool wallStakeLift,
//                      Ilift& robotWithLift,
//                      PrototypeLiftState& state) {
//     Brain.Screen.setCursor(3, 2);
//     switch(state) {
//         case PrototypeLiftState::START:
//             robotWithLift.lift(0);
//             state = PrototypeLiftState::DEFAULT_LOWEST_HEIGHT;
//             Brain.Screen.print("START");
//             break;
//         case PrototypeLiftState::DEFAULT_LOWEST_HEIGHT:

//             break;

//     }
// }