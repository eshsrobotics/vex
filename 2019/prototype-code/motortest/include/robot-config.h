using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontRightWheel;
extern motor FrontLeftWheel;
extern motor BackRightWheel;
extern motor BackLeftWheel;
extern motor LeftIntake;
extern motor RightIntake;
extern motor IntakeLift;
extern motor TrayPusher;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );