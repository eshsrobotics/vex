#ifndef __UPDATE_LIFT_STATE_INCLUDED__
#define __UPDATE_LIFT_STATE_INCLUDED__

#include "Ilift.h"

enum class LiftState;

/**
 * The value that must be initially passed into updateLiftState() to start the
 * state machine.
 */
extern LiftState INITIAL_LIFT_STATE;

/**
 * Moves the lift motor motors incrementally in response to button presses. This
 * needs to be called inside a loop once per frame.
 * @param upButton the state of the button controlling upward movement
 * @param downButton the state of the button controlling downward movement
 * @param robotWithLift an Ilift instance that can drive a lift motor group
 * @param state[out] the current state of the lift, must be maintained by the
 * caller. The value passed in initially must be INITIAL_LIFT_STATE.
 */
void updateLiftState(bool upButton, bool downButton,
                     Ilift& robotWithLift, LiftState& state);

#endif __UPDATE_LIFT_STATE_INCLUDED__
