/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>  // std::swap
#include <vector>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

// If this variable is true, mecanumDrive() will slow to SNEAK_PERCENTAGE of
// normal velocity.  Default is false.
extern bool sneak;

extern const double SNEAK_PERCENTAGE;
extern const double INTAKE_LIFT_VELOCITY;
extern const double TRAY_PUSH_VELOCITY;


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)