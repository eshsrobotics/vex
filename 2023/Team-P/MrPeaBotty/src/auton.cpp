#include "auton.h"
#include "armSubsystem.h"
#include "hardwareConstitution.h"
#include "input.h"
#include <algorithm>

using namespace vex;
using namespace std; 

// This is our current auton plan. Right now, it just drive for 1 sec.
std::vector<AutonStep> autonPlan = {
    {DRIVE_FWD, 50, 0}, 
    {OPEN_CLAW, +1, 0},
    {DRIVE_FWD, 0, 1000}
};

int compareAutonSteps(const AutonStep& a, const AutonStep& b) {
    return a.startTimeMS - b.startTimeMS;
}

//void executeAutonPlan(vector<AutonStep>& autonPlan) {
    // 1.) Sort auton plan by starting time.
//    sort(autonPlan.begin(), autonPlan.end(), compareAutonSteps);

    // 2.) Set index to 0. (Points to 1st auton step)
    // 3.) Reset timer.
//    int index = 0;
//    double driveSpeedPct = 0;
  //  double armSpeedPct = 0;
 //   double turnSpeedPct = 0;
 //   ClawState clawState = CLAW_NEUTRAL;
  //  double startTimeSec = Brain.timer(vex::timeUnits::sec);

    // 4.) Until we have executed the last step:
//     while (index < autonPlan.size()) {

//         double startTimeMS = autonPlan[index].startTimeMS;
//         AutonAction action = autonPlan[index].action;
//         double parameter = autonPlan[index].parameter;

//         // 4.1.) If timer has surpassed current step's start time: 
//         double elapsedTimeSec = Brain.timer(vex::timeUnits::sec) - startTimeSec;
        
//         if (startTimeMS > elapsedTimeSec * 1000) {
//             // 4.1.1.) Decide what to do based on current step.
//             switch (action) {
//                 case DRIVE_FWD:
//                     driveSpeedPct = parameter;
//                     // turnSpeedPct = 0; Commenting out this line would allow us to drive and turn at the same time.
//                     break;
                
//                 case TURN_CLOCKWISE:
//                     turnSpeedPct = parameter;
//                      // turnSpeedPct = 0; Commenting out this line would allow us to drive and turn at the same time.
//                     break;

//                 case MOVE_ARM:
//                     armSpeedPct = parameter;
//                     break;
                
//                 case OPEN_CLAW:
//                     if (parameter > 0) {
//                         clawState = CLAW_OPEN;
//                     } else if (parameter == 0) {
//                         clawState = CLAW_NEUTRAL;
//                     } else {
//                         clawState = CLAW_CLOSE;
//                     }
//                     break;
//             }
//             // 4.1.2.) Execute robot logic for current step.
//             arcade_drive_by_quadrant(turnSpeedPct, driveSpeedPct);
//             // moveArm(armSpeedPct, clawState, armMotorLeft, armMotorRight, clawMotor);

//             // 4.1.2.) Increments index. (Moves to next step)
//             index++;

//         } // (if the current step is due to run.)

//         wait(10, vex::timeUnits::msec);
//     } // (while there are steps to execute.)
    
// };