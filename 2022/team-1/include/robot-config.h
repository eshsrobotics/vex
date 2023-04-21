using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor leftFront;
extern motor rightFront;
extern motor leftBack;
extern motor rightBack;
extern signature VisionSensor__DISLIKED_CUBE;
extern signature VisionSensor__LIKED_CUBE;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;
extern line BackRightTracker;
extern line BackLeftTracker;
extern led LED_RED;
extern motor cameraMotor;
extern line FrontRightTracker;
extern line FrontLeftTracker;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );