using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor BackRight;
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackLeft;
extern signature VisionSensor__ORANGE_BOX;
extern signature VisionSensor__GREEN_BOX;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );