// Implements and definition updateLiftState.h

#include "updateLiftState.h"

#include <algorithm> // abs()
#include <string>

#include "vex.h"

using std::abs;
using std::string;

/**
 * A list of all the states that the state machine for lifts will use. All of
 * the states were documented in docs/lift-state-maching.png
 */
enum class LiftState {

    // Initial state of the state machine
    // - transitions: default (unconditional)
    START,
    DEFAULT_LOWEST_HEIGHT,
    DEFAULT_UP,
    MOBILE_GOAL,
    MOBILE_GOAL_DOWN,
    MOBILE_GOAL_UP,
    WALL_STAKE,
    WALL_STAKE_DOWN,
    WALL_STAKE_UP,
    ALLIANCE_STAKE,
    ALLIANCE_STAKE_DOWN,

};

// The lift is an abstraction that can go from the lowest position at 0.0 to the
// highest position at 1.0.  Somewhere along the way, there are various "stops"
// that represent the heights that the lift needs to go to to reach of our
// destinations:
//
//   - The ground
//   - The (top of the) mobile goal
//   - The (top of the) alliance stake
//   - The (top of the) wall stake
//
// These values vary from robot to robot.
LiftState INITIAL_LIFT_STATE = LiftState::START;

void updateLiftState(
    bool upButton,
    bool downButton,
    Ilift& robotWithLift,
    LiftState& state
) {
    const double defaultHeight = robotWithLift.liftHeights().defaultHeight;
    const double mobileGoalHeight =
        robotWithLift.liftHeights().mobileGoalHeight;
    const double allianceStakeHeight =
        robotWithLift.liftHeights().allianceStakeHeight;
    const double wallStakeHeight = robotWithLift.liftHeights().wallStakeHeight;

    const char* format = "Next State: %s";
    const char* label = "";

    switch (state) {
        case LiftState::START:
            state = LiftState::DEFAULT_LOWEST_HEIGHT;
            label = "Start";
            break;

        case LiftState::DEFAULT_LOWEST_HEIGHT:
            if (upButton) {
                state = LiftState::DEFAULT_UP;
                label = "Default up";
                robotWithLift.moveLiftDirect(mobileGoalHeight - defaultHeight);
            } else {
                robotWithLift.moveLiftDirect(0);
            }
            break;

        case LiftState::DEFAULT_UP: // Heading up to the mobile goal height
            if (!robotWithLift.isLiftSpinning()) {
                robotWithLift.moveLiftDirect(0);
                if (!upButton) {
                    state = LiftState::MOBILE_GOAL;
                    label = "Mobile goal";
                }
            }
            break;

        case LiftState::MOBILE_GOAL:
            // Allow the user to go either up or down, but not both.
            if (upButton && !downButton) {
                state = LiftState::MOBILE_GOAL_UP;
                label = "Mobile goal up";
                robotWithLift.moveLiftDirect(
                    wallStakeHeight - mobileGoalHeight
                );
            } else if (downButton && !upButton) {
                state = LiftState::MOBILE_GOAL_DOWN;
                label = "Mobile goal down";
                robotWithLift.moveLiftDirect(defaultHeight - mobileGoalHeight);
            } else {
                robotWithLift.moveLiftDirect(0);
            }
            break;

        case LiftState::MOBILE_GOAL_UP:
            if (!robotWithLift.isLiftSpinning()) {
                robotWithLift.moveLiftDirect(0);
                if (!upButton) {
                    state = LiftState::WALL_STAKE;
                    label = "Wall stake";
                }
            }
            break;

        case LiftState::MOBILE_GOAL_DOWN: // Heading down to the lowest height
            if (!robotWithLift.isLiftSpinning()) {
                robotWithLift.moveLiftDirect(0);
                if (!downButton) {
                    state = LiftState::DEFAULT_LOWEST_HEIGHT;
                    label = "Default";
                }
            }
            break;

        case LiftState::WALL_STAKE:
            if (downButton && !upButton) {
                state = LiftState::WALL_STAKE_DOWN;
                label = "Wall stake down";
                robotWithLift.moveLiftDirect(
                    mobileGoalHeight - wallStakeHeight
                );
            } else if (upButton && !downButton) {
                state = LiftState::WALL_STAKE_UP;
                label = "Wall stake up";
                robotWithLift.moveLiftDirect(
                    allianceStakeHeight - wallStakeHeight
                );
            } else {
                robotWithLift.moveLiftDirect(0);
            }
            break;

        case LiftState::WALL_STAKE_DOWN: // Heading down to the alliance stake
                                         // height
            if (!robotWithLift.isLiftSpinning()) {
                robotWithLift.moveLiftDirect(0);
                if (!downButton) {
                    state = LiftState::MOBILE_GOAL;
                    label = "Mobile goal";
                }
            }
            break;

        case LiftState::WALL_STAKE_UP: // Heading up to the wall stake height
            if (!robotWithLift.isLiftSpinning()) {
                robotWithLift.moveLiftDirect(0);
                if (!upButton) {
                    state = LiftState::ALLIANCE_STAKE;
                    label = "Alliance stake";
                }
            }
            break;

        case LiftState::ALLIANCE_STAKE:
            if (downButton) {
                state = LiftState::ALLIANCE_STAKE_DOWN;
                label = "Alliance stake down";
                robotWithLift.moveLiftDirect(
                    wallStakeHeight - allianceStakeHeight
                );
            } else {
                robotWithLift.moveLiftDirect(0);
            }
            break;

        case LiftState::ALLIANCE_STAKE_DOWN: // Heading down to the mobile goal
                                             // height
            if (!robotWithLift.isLiftSpinning()) {
                robotWithLift.moveLiftDirect(0);
                if (!downButton) {
                    state = LiftState::WALL_STAKE;
                    label = "Wall stake";
                }
            }
            break;
    }

    Controller.Screen.setCursor(CONTROLLER_LIFT_STATE_ROW, 1);
    Controller.Screen.print(format, label);
}