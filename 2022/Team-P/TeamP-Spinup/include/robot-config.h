using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor_group Intakemotors;
extern drivetrain Drivetrain;
extern motor_group Flywheel;
extern motor roller;
extern digital_out expansionLeft;
extern digital_out expansionRight;
extern signature VisionSensor__RED_BASKET;
extern signature VisionSensor__BLUE_BASKET;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );