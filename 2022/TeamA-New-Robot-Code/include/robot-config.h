using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftBack;
extern motor LeftMiddle;
extern motor LeftFront;
extern motor RightBack;
extern motor RightMiddle;
extern motor RightFront;
extern controller Controller1;
extern motor intake;
extern motor flywheel;
extern distance distanceSensor;
extern digital_out LeftPneumatic;
extern digital_out RightPneumatic;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );