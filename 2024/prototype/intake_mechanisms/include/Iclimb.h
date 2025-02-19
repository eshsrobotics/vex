#pragma once
#include "vex.h"

/**
 * An interface for interacting with the pneumatics involved in activating the
 * climb mechanism.
 */

class Iclimb {
  public:
    /**
     * This code was initially for the climb hooks, which have been defeatured.
     * Now, the climb pneumatics are being used for a doinker. The doinker is a
     * hammer on the front right of the robot that can come down and grab onto
     * mobile goals for the robot to drag around.
     * 
     * @param active true to deploy the doinker, false to retract it
     */
    virtual void activateClimb(bool active) = 0;
};