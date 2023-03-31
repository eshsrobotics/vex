using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor flywheel_Left;
extern motor flywheel_Right;
extern motor intake;
extern motor29 front_Right_1;
extern motor29 front_Right_2;
extern motor29 front_Left_1;
extern motor29 front_Left_2;
extern motor29 back_Right_2;
extern motor29 back_Left_1;
extern motor29 back_Left_2;
extern motor29 back_Right_1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );