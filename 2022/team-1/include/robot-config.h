using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor leftFront;
extern motor rightFront;
extern motor leftBack;
extern motor rightBack;
extern signature Vision__ORANGE_CUBE;
extern signature Vision__GREEN_CUBE;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern line LeftLineTracker;
extern line RightLineTracker;
extern servo Camera_motor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );