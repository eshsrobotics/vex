using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor m;
extern motor Motor2;
extern motor Motor3;
extern motor Motor4;
extern controller Controller1;
extern smartdrive Drivetrain;
extern gps DrivetrainGPS;
extern optical Optical6;
extern rotation Rotation7;
extern distance Distance8;
extern gps GPS9;
extern line LineTrackerA;
extern light LightB;
extern potV2 PotentiometerV2C;
extern digital_out DigitalOutD;
extern signature Vision14__SIG_1;
extern signature Vision14__SIG_2;
extern signature Vision14__SIG_3;
extern signature Vision14__SIG_4;
extern signature Vision14__SIG_5;
extern signature Vision14__SIG_6;
extern signature Vision14__SIG_7;
extern vision Vision14;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );