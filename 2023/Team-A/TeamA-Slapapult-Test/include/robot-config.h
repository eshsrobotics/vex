using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor slapapult_motor;
extern limit limit_switch;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );