using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor UpperFlywheel;
extern motor LowerFlywheel;
extern pot UpperFlywheelPot;
extern pot LowerFlywheelPot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );