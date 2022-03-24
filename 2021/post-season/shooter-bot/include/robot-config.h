using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor PunchMotor;
extern motor29 IntakeMotor;
extern motor29 LeftMotor;
extern motor29 RightMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );