#pragma once
#include "vex.h"

/**
 * An interface for interacting with the pneumatics involved in activating the
 * climb mechanism.
 */

class Iclimb {
  public:
    /**
     * Makes the climb hooks activate and go up. The hooks are down by
     * default and we don't need them during auton, so there is no need to
     * make the hooks go back down after the piston is activated.
     * Additionally, since the piston is activated to make the hooks go up,
     * the set boolean will always be true. Lastly, the button only needs to
     * be pressed once, even though the function is being called over and
     * over again in the teleop function.
     */
    virtual void activateClimb() = 0;
};