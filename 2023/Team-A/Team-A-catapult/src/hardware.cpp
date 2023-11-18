#include "vex.h"
#include "hardware.h"

using namespace vex;
brain Brain;
controller Controller = controller(primary);
// motor format: motor(port, reversed) where 'port' is an integer for the port
// number and 'reversed' is a boolean for if the motor needs to be reversed or not
motor catapult = motor(CATAPULT_PORT, false);
distance triballDetector = distance(DISTANCE_PORT);

void vexcodeInit(void) {
}