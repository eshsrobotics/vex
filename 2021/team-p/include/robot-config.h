using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Left_Motor;
extern motor Right_Motor;
extern controller Controller1;
extern motor Arm_Right;
extern motor Arm_Left;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );