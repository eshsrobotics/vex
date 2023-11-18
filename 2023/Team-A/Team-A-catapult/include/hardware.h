#ifndef HARDWARE_H_IS_PRESENT
#define HARDWARE_H_IS_PRESENT

#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

const int CATAPULT_PORT = 1 - 1;
const int DISTANCE_PORT = 2 - 1;

// Don't know actual value
const double DISTANCE_SENSOR_DETECT_TRIBALL = 1.0;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::motor catapult;
extern vex::distance triballDetector;

void vexcodeInit(void);
#endif // (#ifndef HARDWARE_H_IS_PRESENT)