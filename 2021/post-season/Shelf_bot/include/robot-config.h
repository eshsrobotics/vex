using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor29 leftMotor;
extern motor29 rightMotor;
extern motor29 middleMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );