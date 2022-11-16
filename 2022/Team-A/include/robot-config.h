using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor launcher_left;
extern motor launcher_right;
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor intake;
extern motor roller;
extern distance distanceSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );