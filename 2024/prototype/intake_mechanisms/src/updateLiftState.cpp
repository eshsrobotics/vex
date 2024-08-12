// Implements and definition updateLiftState.h

#include "updateLiftState.h"

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