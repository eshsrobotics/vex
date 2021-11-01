/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "v5.h"
#include "v5_vcs.h"

#include "Autonomous_Routines.h"
#include "Display_Information.h"
#include "Drivesetup.h"
#include "autonomousPhase.h"
#include "robot-config.h"
#include "preAuton.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)