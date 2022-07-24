using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor PunchMotor;
extern motor29 IntakeMotor;
extern motor29 LeftMotor;
extern motor29 RightMotor;
extern motor29 TransferMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );