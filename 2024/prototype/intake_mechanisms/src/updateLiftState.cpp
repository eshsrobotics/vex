// Implements and definition updateLiftState.h

#include "updateLiftState.h"
#include "vex.h"
#include <algorithm>  // abs()

using std::abs;

enum class LiftState {

    // Initial state of the state machine
    // - transitions: default (unconditional)
    START,
    DEFAULT_LOWEST_HEIGHT,
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

// The lift is an abstraction that can go from the lowest position at 0.0 to the
// highest position at 1.0.  Somewhere along the way, there are various "stops"
// that represent the heights that the lift needs to go to to reach of our destinations:
//
//   - The ground
//   - The (top of the) mobile goal
//   - The (top of the) alliance stake
//   - The (top of the) wall stake
//
// These values vary from robot to robot.
LiftState INITIAL_LIFT_STATE = LiftState::START;

void updateLiftState(bool upButton, bool downButton,
                     Ilift& robotWithLift, LiftState& state) {

    // The position that the lift reaches can vary by up to this value and still
    // be considered to be on-target.
    // Adjust as needed.
    const double deadzone = 0.03;

    const double position = robotWithLift.liftPosition();
    const double defaultHeight = robotWithLift.liftHeights().defaultHeight;
    const double mobileGoalHeight = robotWithLift.liftHeights().mobileGoalHeight;
    const double allianceStakeHeight = robotWithLift.liftHeights().allianceStakeHeight;
    const double wallStakeHeight = robotWithLift.liftHeights().wallStakeHeight;

    bool reachedDefaultHeight = abs(position - defaultHeight) < deadzone;
    bool reachedMobileGoalHeight = abs(position - mobileGoalHeight) < deadzone;
    bool reachedAllianceStakeHeight = abs(position - allianceStakeHeight) < deadzone;
    bool reachedWallStakeHeight = abs(position - wallStakeHeight) < deadzone;

    Brain.Screen.setCursor(6, 10);
    const char* format = "Next State: %s      ";

    switch (state) {
        case LiftState::START:
            state = LiftState::DEFAULT_LOWEST_HEIGHT;
            Brain.Screen.print(format, "Start");
            break;

        case LiftState::DEFAULT_LOWEST_HEIGHT:
            if (upButton) {
                state = LiftState::DEFAULT_UP;
                Brain.Screen.print(format, "Default up");
            }
            break;

        case LiftState::DEFAULT_UP: // Heading up to the mobile goal height
            if (reachedMobileGoalHeight) {
                robotWithLift.lift(0);
                if (!upButton) {
                    state = LiftState::MOBILE_GOAL;
                    Brain.Screen.print(format, "Mobile goal");
                }
            }
            break;

        case LiftState::MOBILE_GOAL_UP:
            if (reachedAllianceStakeHeight){
                robotWithLift.lift(0);
                if (!upButton) {
                    state = LiftState::ALLIANCE_STAKE;
                    Brain.Screen.print(format, "Alliance stake");
                }
            }
            break;

        case LiftState::MOBILE_GOAL_DOWN: // Heading down to the lowest height
            if (reachedDefaultHeight) {
                robotWithLift.lift(0);
                if (!downButton) {
                    state = LiftState::DEFAULT_LOWEST_HEIGHT;
                    Brain.Screen.print(format, "Default");
                }
            }
            break;

        case LiftState::MOBILE_GOAL:
            // Allow the user to go either up or down, but not both.
            if (upButton && !downButton) {
                state = LiftState::MOBILE_GOAL_UP;
                Brain.Screen.print(format, "Mobile goal up");
            } else if (downButton && !upButton) {
                state = LiftState::MOBILE_GOAL_DOWN;
                Brain.Screen.print(format, "Mobile goal down");
            }
            break;

        case LiftState::ALLIANCE_STAKE_UP: // Heading up to the wall stake height
            if (reachedWallStakeHeight) {
                robotWithLift.lift(0);
                if (!upButton) {
                    state = LiftState::WALL_STAKE;
                    Brain.Screen.print(format, "Wall stake");
                }
            }
            break;

        case LiftState::ALLIANCE_STAKE_DOWN: //Heading down to the mobile goal height
             if (reachedMobileGoalHeight) {
                robotWithLift.lift(0);
                if (!downButton) {
                    state = LiftState::MOBILE_GOAL;
                    Brain.Screen.print(format, "Mobile goal");
                }
            }
            break;

        case LiftState::ALLIANCE_STAKE:
            if (upButton && !downButton) {
                state = LiftState::ALLIANCE_STAKE_UP;
                Brain.Screen.print(format, "Alliance stake down");
            } else if (downButton && upButton) {
                state = LiftState::ALLIANCE_STAKE_DOWN;
                Brain.Screen.print(format, "Alliance stake up");
            }
            break;

        case LiftState::WALL_STAKE_DOWN: // Heading down to the alliance stake height
            if (reachedAllianceStakeHeight) {
                robotWithLift.lift(0);
                if (!downButton) {
                    state = LiftState::ALLIANCE_STAKE;
                    Brain.Screen.print(format, "Alliance stake");
                }
            }
            break;

        case LiftState::WALL_STAKE:
            if (downButton) {
                state = LiftState::WALL_STAKE_DOWN;
                Brain.Screen.print(format, "Wall stake down");
            }
            break;
    }

}