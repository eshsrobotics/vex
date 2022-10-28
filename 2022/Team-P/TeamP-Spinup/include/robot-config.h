using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor TopIntake;
extern motor LowerIntake;
extern controller Controller1;
extern motor LeftDriveMotor;
extern motor RightDriveMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );