using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor LeftLiftMotor;
extern motor ArmMotorRight;
extern motor ArmMotorLeft;
extern digital_out PneumaticSpatula;
extern motor pMotor;
extern digital_out PneumaticClaw;
extern motor RightLiftMotor;
extern motor FrontLeftMotor;
extern motor FrontRightMotor;
extern motor RearLeftMotor;
extern motor RearRightMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );