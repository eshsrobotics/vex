using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor LiftMotor;
extern motor ArmMotorRight;
extern motor ArmMotorLeft;
extern digital_out Pneumatics1;
extern motor pMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );