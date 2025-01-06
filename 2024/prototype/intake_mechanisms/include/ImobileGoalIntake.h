#pragma once
#include "vex.h"

/**
 * An interface for interacting with the pneumatics clamp for interacting with
 * mobile goals.
*/
class ImobileGoalIntake {
    public:
        /**
         * Clamps and unclamps the mobile goal grabber. This method is a
         * non-blocking call, and it takes non-zero time for the clamp to
         * complete; this method initiates the clamping process.
         * @param active true for the clamp to close and false for open
         */
        virtual void clamp(bool active) = 0;
};