using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor front_left;
extern motor front_right;
extern motor back_left;
extern motor back_right;
extern motor launcher_left;
extern motor launcher_right;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );