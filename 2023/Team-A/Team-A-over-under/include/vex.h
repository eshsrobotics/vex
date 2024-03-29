// VEX.H: Common includes for VEX and C++ libraries

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "v5.h"
#include "v5_vcs.h"
#include "hardware.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)